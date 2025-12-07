#define NOMINMAX
#include "raylib.h"

#include <iostream>
#include <string>
#include <vector>
#include <queue>
#include <algorithm>
#include <cstdlib>
#include <cmath> 
#include <map>

#if defined(_MSC_VER)
#pragma comment(lib, "raylib.lib")
#pragma comment(lib, "winmm.lib")
#pragma comment(lib, "kernel32.lib")
#pragma comment(lib, "opengl32.lib")
#pragma comment(lib, "gdi32.lib")
#pragma comment(lib, "user32.lib")
#pragma comment(lib, "shell32.lib")
#endif

using namespace std;

// Forward declarations
class RuleThreeBase;
class ProductHashTable;
class Graph;
class OrderPriorityQueue;
class Customer;
class SystemClass;
class Admin;

struct Product {
    int id;
    string name;
    double price;
    int stock;
};

struct Node {
    Product p;
    Node* left;
    Node* right;
    Node(Product prod) : p(prod), left(nullptr), right(nullptr) {}
};

class RuleThreeBase {
public:
    RuleThreeBase() {}
    RuleThreeBase(const RuleThreeBase&) {}
    RuleThreeBase& operator=(const RuleThreeBase&) { return *this; }
    virtual ~RuleThreeBase() {}
};

class ProductHashTable {
private:
    static const int TABLE_SIZE = 17;
    vector<vector<Product*>> table;

    int hashFunc(int key) const {
        return key % TABLE_SIZE;
    }

public:
    ProductHashTable() {
        table.resize(TABLE_SIZE);
    }

    void insert(Product* p) {
        int h = hashFunc(p->id);
        table[h].push_back(p);
    }

    Product* search(int id) {
        int h = hashFunc(id);
        for (auto prod : table[h]) {
            if (prod->id == id) {
                return prod;
            }
        }
        return nullptr;
    }

    void clear() {
        for (size_t i = 0; i < table.size(); ++i)
            table[i].clear();
    }

    void rebuild(Product* products, int count) {
        clear();
        for (int i = 0; i < count; i++) {
            insert(&products[i]);
        }
    }
};

class Graph {
private:
    vector<vector<int>> adj;

public:
    Graph(int n = 0) { adj.resize(n); }
    Graph(const Graph& other) { adj = other.adj; }
    Graph& operator=(const Graph& other) {
        if (this != &other) { adj = other.adj; }
        return *this;
    }
    void resize(int n) { adj.assign(n, vector<int>()); }
    void addEdge(int u, int v) {
        if (u >= 0 && v >= 0 && u < (int)adj.size() && v < (int)adj.size()) {
            adj[u].push_back(v);
            adj[v].push_back(u);
        }
    }
    const vector<vector<int>>& getAdjacency() const { return adj; }
};

struct OrderInfo {
    int orderID;
    int priority;
    string userName;
    vector<Product> items;
};

class OrderPriorityQueue {
private:
    vector<OrderInfo> heap;

    void heapifyUp(int index) {
        while (index > 0) {
            int parent = (index - 1) / 2;
            if (heap[index].priority < heap[parent].priority) {
                swap(heap[index], heap[parent]);
                index = parent;
            }
            else break;
        }
    }

    void heapifyDown(int index) {
        int n = (int)heap.size();
        while (true) {
            int left = 2 * index + 1;
            int right = 2 * index + 2;
            int smallest = index;

            if (left < n && heap[left].priority < heap[smallest].priority)
                smallest = left;
            if (right < n && heap[right].priority < heap[smallest].priority)
                smallest = right;

            if (smallest != index) {
                swap(heap[index], heap[smallest]);
                index = smallest;
            }
            else break;
        }
    }

public:
    OrderPriorityQueue() {}
    OrderPriorityQueue(const OrderPriorityQueue& other) : heap(other.heap) {}
    OrderPriorityQueue& operator=(const OrderPriorityQueue& other) {
        if (this != &other) { heap = other.heap; }
        return *this;
    }

    void push(int orderID, int priority, const string& userName, const vector<Product>& items) {
        heap.push_back({ orderID, priority, userName, items });
        heapifyUp((int)heap.size() - 1);
    }
    bool empty() const { return heap.empty(); }
    OrderInfo top() const { return heap.front(); }
    void pop() {
        if (heap.empty()) return;
        heap[0] = heap.back();
        heap.pop_back();
        if (!heap.empty()) heapifyDown(0);
    }
    void clear() { heap.clear(); }
    vector<OrderInfo> getHeapSnapshot() const { return heap; }
};

class Customer : public RuleThreeBase {
private:
    struct CartNode {
        Product p;
        CartNode* next;
        CartNode(Product prod) : p(prod), next(nullptr) {}
    };

    CartNode* cartHead;

    struct StackNode {
        Product p;
        StackNode* next;
        StackNode(Product prod) : p(prod), next(nullptr) {}
    };

    StackNode* topView;

    CartNode* copyCartList(CartNode* otherHead) {
        if (!otherHead) return nullptr;
        CartNode* newHead = new CartNode(otherHead->p);
        CartNode* tail = newHead;
        CartNode* current = otherHead->next;
        while (current) {
            tail->next = new CartNode(current->p);
            tail = tail->next;
            current = current->next;
        }
        return newHead;
    }

    StackNode* copyStack(StackNode* otherTop) {
        if (!otherTop) return nullptr;
        vector<Product> temp;
        StackNode* cur = otherTop;
        while (cur) {
            temp.push_back(cur->p);
            cur = cur->next;
        }
        StackNode* newTop = nullptr;
        for (int i = (int)temp.size() - 1; i >= 0; --i) {
            StackNode* n = new StackNode(temp[i]);
            n->next = newTop;
            newTop = n;
        }
        return newTop;
    }

    void clearCart() {
        while (cartHead) {
            CartNode* t = cartHead;
            cartHead = cartHead->next;
            delete t;
        }
    }

    void clearStack() {
        while (topView) {
            StackNode* t = topView;
            topView = topView->next;
            delete t;
        }
    }

public:
    Customer() : cartHead(nullptr), topView(nullptr) {}

    Customer(const Customer& other) : RuleThreeBase(other) {
        cartHead = copyCartList(other.cartHead);
        topView = copyStack(other.topView);
    }

    Customer& operator=(const Customer& other) {
        if (this == &other) return *this;
        clearCart();
        clearStack();
        cartHead = copyCartList(other.cartHead);
        topView = copyStack(other.topView);
        return *this;
    }

    ~Customer() {
        clearCart();
        clearStack();
    }

    void addToCart(Product p) {
        CartNode* n = new CartNode(p);
        n->next = cartHead;
        cartHead = n;
    }

    void pushRecent(Product p) {
        StackNode* n = new StackNode(p);
        n->next = topView;
        topView = n;
    }

    vector<Product> getCartItems() const {
        vector<Product> out;
        CartNode* cur = cartHead;
        while (cur) {
            out.push_back(cur->p);
            cur = cur->next;
        }
        return out;
    }

    vector<Product> getRecentViews() const {
        vector<Product> out;
        StackNode* cur = topView;
        while (cur) {
            out.push_back(cur->p);
            cur = cur->next;
        }
        return out;
    }

    void clearCartAfterCheckout() {
        clearCart();
        cartHead = nullptr;
    }
};

class SystemClass : public RuleThreeBase {
private:
    struct QNode {
        int orderID;
        string userName;
        vector<Product> items;
        QNode* next;
        QNode(int id, const string& user, const vector<Product>& itms)
            : orderID(id), userName(user), items(itms), next(nullptr) {
        }
    };

    QNode* front;
    QNode* rear;

    struct AVL {
        string name;
        Customer userCartData;
        int height;
        AVL* left;
        AVL* right;

        AVL(string n) : name(n), userCartData(), height(1), left(nullptr), right(nullptr) {}
    };

    AVL* userRoot;
    OrderPriorityQueue priorityOrders;
    int nextOrderID;

    int height(AVL* n) { return (n == nullptr ? 0 : n->height); }
    int getBalance(AVL* n) {
        if (!n) return 0;
        return height(n->left) - height(n->right);
    }

    AVL* rightRotate(AVL* y) {
        AVL* x = y->left;
        AVL* T2 = x->right;
        x->right = y;
        y->left = T2;
        y->height = std::max(height(y->left), height(y->right)) + 1;
        x->height = std::max(height(x->left), height(x->right)) + 1;
        return x;
    }

    AVL* leftRotate(AVL* x) {
        AVL* y = x->right;
        AVL* T2 = y->left;
        y->left = x;
        x->right = T2;
        x->height = std::max(height(x->left), height(x->right)) + 1;
        y->height = std::max(height(y->left), height(y->right)) + 1;
        return y;
    }

    AVL* insertAVL(AVL* node, const string& key) {
        if (node == nullptr)
            return new AVL(key);
        if (key < node->name)
            node->left = insertAVL(node->left, key);
        else if (key > node->name)
            node->right = insertAVL(node->right, key);
        else
            return node;

        node->height = 1 + std::max(height(node->left), height(node->right));
        int balance = getBalance(node);
        if (balance > 1 && key < node->left->name)
            return rightRotate(node);
        if (balance < -1 && key > node->right->name)
            return leftRotate(node);
        if (balance > 1 && key > node->left->name) {
            node->left = leftRotate(node->left);
            return rightRotate(node);
        }
        if (balance < -1 && key < node->right->name) {
            node->right = rightRotate(node->right);
            return leftRotate(node);
        }
        return node;
    }

    void inorderUsersHelper(AVL* root, vector<string>& out) {
        if (!root) return;
        inorderUsersHelper(root->left, out);
        out.push_back(root->name);
        inorderUsersHelper(root->right, out);
    }

    AVL* copyAVL(AVL* root) {
        if (!root) return nullptr;
        AVL* newRoot = new AVL(root->name);
        newRoot->userCartData = root->userCartData;
        newRoot->height = root->height;
        newRoot->left = copyAVL(root->left);
        newRoot->right = copyAVL(root->right);
        return newRoot;
    }

    void destroyAVL(AVL* root) {
        if (!root) return;
        destroyAVL(root->left);
        destroyAVL(root->right);
        delete root;
    }

    AVL* findUserNode(AVL* root, const string& name) {
        if (!root) return nullptr;
        if (name == root->name) return root;
        if (name < root->name) return findUserNode(root->left, name);
        return findUserNode(root->right, name);
    }

    void clearQueue() {
        while (front) {
            QNode* t = front;
            front = front->next;
            delete t;
        }
        rear = nullptr;
    }

    void copyQueue(const SystemClass& other) {
        QNode* cur = other.front;
        while (cur) {
            enqueueOrder(cur->userName, cur->items);
            cur = cur->next;
        }
    }

public:
    SystemClass() : front(nullptr), rear(nullptr), userRoot(nullptr), nextOrderID(1001) {}

    SystemClass(const SystemClass& other) : RuleThreeBase(other) {
        front = rear = nullptr;
        nextOrderID = other.nextOrderID;
        copyQueue(other);
        userRoot = copyAVL(other.userRoot);
        priorityOrders = other.priorityOrders;
    }

    SystemClass& operator=(const SystemClass& other) {
        if (this == &other) return *this;
        clearQueue();
        destroyAVL(userRoot);
        nextOrderID = other.nextOrderID;
        copyQueue(other);
        userRoot = copyAVL(other.userRoot);
        priorityOrders = other.priorityOrders;
        return *this;
    }

    ~SystemClass() {
        clearQueue();
        destroyAVL(userRoot);
        priorityOrders.clear();
    }

    Customer* getUserCartData(const string& name) {
        AVL* node = findUserNode(userRoot, name);
        if (node) {
            return &(node->userCartData);
        }
        return nullptr;
    }

    int enqueueOrder(const string& userName, const vector<Product>& items) {
        int orderID = nextOrderID++;
        QNode* n = new QNode(orderID, userName, items);
        if (!rear) front = rear = n;
        else { rear->next = n; rear = n; }
        return orderID;
    }

    bool dequeueOrderOnce(OrderInfo& processedOrder) {
        if (!front) return false;
        processedOrder.orderID = front->orderID;
        processedOrder.userName = front->userName;
        processedOrder.items = front->items;
        processedOrder.priority = 0;
        QNode* t = front;
        front = front->next;
        if (!front) rear = nullptr;
        delete t;
        return true;
    }

    vector<OrderInfo> getQueueSnapshot() const {
        vector<OrderInfo> res;
        QNode* cur = front;
        while (cur) {
            res.push_back({ cur->orderID, 0, cur->userName, cur->items });
            cur = cur->next;
        }
        return res;
    }

    void addUser(const string& name) {
        if (name.empty()) return;
        userRoot = insertAVL(userRoot, name);
    }

    vector<string> getUsersInOrder() {
        vector<string> out;
        inorderUsersHelper(userRoot, out);
        return out;
    }

    void enqueuePriorityOrder(const string& userName, const vector<Product>& items, int priority) {
        int orderID = nextOrderID++;
        priorityOrders.push(orderID, priority, userName, items);
    }

    bool processOnePriorityOrder(OrderInfo& out) {
        if (priorityOrders.empty()) return false;
        out = priorityOrders.top();
        priorityOrders.pop();
        return true;
    }

    vector<OrderInfo> getPriorityOrdersSnapshot() const {
        return priorityOrders.getHeapSnapshot();
    }
};

class Admin : public RuleThreeBase {
private:
    Product* products;
    int productCount;
    int productCapacity;

    Product** categories;
    int* categorySizes;
    int categoryCount;

    Node* root;
    ProductHashTable hashTable;
    Graph recommendationGraph;

    Node* insertBST(Node* n, Product p) {
        if (!n) return new Node(p);
        if (p.id < n->p.id) n->left = insertBST(n->left, p);
        else if (p.id > n->p.id) n->right = insertBST(n->right, p);
        return n;
    }

    void destroyTree(Node* n) {
        if (!n) return;
        destroyTree(n->left);
        destroyTree(n->right);
        delete n;
    }

    void rebuildBST() {
        destroyTree(root);
        root = nullptr;
        for (int i = 0; i < productCount; ++i) {
            root = insertBST(root, products[i]);
        }
        hashTable.rebuild(products, productCount);
    }

    void merge(Product arr[], int l, int m, int r) {
        int n1 = m - l + 1;
        int n2 = r - m;
        vector<Product> L(n1), R(n2);
        for (int i = 0; i < n1; i++) L[i] = arr[l + i];
        for (int j = 0; j < n2; j++) R[j] = arr[m + 1 + j];
        int i = 0, j = 0, k = l;
        while (i < n1 && j < n2) {
            if (L[i].price <= R[j].price)
                arr[k++] = L[i++];
            else
                arr[k++] = R[j++];
        }
        while (i < n1) arr[k++] = L[i++];
        while (j < n2) arr[k++] = R[j++];
    }

    void mergeSort(Product arr[], int l, int r) {
        if (l < r) {
            int m = l + (r - l) / 2;
            mergeSort(arr, l, m);
            mergeSort(arr, m + 1, r);
            merge(arr, l, m, r);
        }
    }

    void ensureCapacity() {
        if (productCount < productCapacity) return;
        int newCap = productCapacity * 2;
        Product* newArr = new Product[newCap];
        for (int i = 0; i < productCount; ++i) newArr[i] = products[i];
        delete[] products;
        products = newArr;
        productCapacity = newCap;
    }

public:
    Admin(int count = 6, int cats = 2) :
        products(new Product[count]), productCount(count), productCapacity(count),
        categories(new Product* [cats]), categorySizes(new int[cats]), categoryCount(cats),
        root(nullptr), hashTable(), recommendationGraph(count)
    {
        for (int i = 0; i < cats; i++) {
            categorySizes[i] = 2;
            categories[i] = new Product[2];
        }
    }

    Admin(const Admin& other) : RuleThreeBase(other) {
        productCount = other.productCount;
        productCapacity = other.productCapacity;
        products = new Product[productCapacity];
        for (int i = 0; i < productCount; i++)
            products[i] = other.products[i];

        categoryCount = other.categoryCount;
        categorySizes = new int[categoryCount];
        categories = new Product * [categoryCount];

        for (int i = 0; i < categoryCount; i++) {
            categorySizes[i] = other.categorySizes[i];
            categories[i] = new Product[categorySizes[i]];
            for (int j = 0; j < categorySizes[i]; j++)
                categories[i][j] = other.categories[i][j];
        }
        root = nullptr;
        hashTable = other.hashTable;
        recommendationGraph = other.recommendationGraph;
        rebuildBST();
    }

    Admin& operator=(const Admin& other) {
        if (this == &other)
            return *this;
        delete[] products;
        for (int i = 0; i < categoryCount; i++) delete[] categories[i];
        delete[] categories;
        delete[] categorySizes;
        destroyTree(root);

        productCount = other.productCount;
        productCapacity = other.productCapacity;
        products = new Product[productCapacity];
        for (int i = 0; i < productCount; i++)
            products[i] = other.products[i];

        categoryCount = other.categoryCount;
        categorySizes = new int[categoryCount];
        categories = new Product * [categoryCount];

        for (int i = 0; i < categoryCount; i++) {
            categorySizes[i] = other.categorySizes[i];
            categories[i] = new Product[categorySizes[i]];
            for (int j = 0; j < categorySizes[i]; j++)
                categories[i][j] = other.categories[i][j];
        }
        root = nullptr;
        hashTable = other.hashTable;
        recommendationGraph = other.recommendationGraph;
        rebuildBST();
        return *this;
    }

    ~Admin() {
        delete[] products;
        for (int i = 0; i < categoryCount; i++) delete[] categories[i];
        delete[] categories;
        delete[] categorySizes;
        destroyTree(root);
        hashTable.clear();
    }

    void initializeProducts() {
        for (int i = 0; i < productCount; i++) {
            products[i] = { 100 + i, "Product" + to_string(i + 1), double(10 + i * 5), 10 + i };
            hashTable.insert(&products[i]);
        }
        for (int c = 0; c < categoryCount; c++) {
            for (int j = 0; j < categorySizes[c]; j++) {
                int idx = (c * 2 + j) % productCount;
                categories[c][j] = products[idx];
            }
        }
        recommendationGraph.resize(productCount);
        for (int i = 0; i < productCount - 1; i++) {
            recommendationGraph.addEdge(i, i + 1);
        }
        rebuildBST();
    }

    void addProduct(const Product& p) {
        ensureCapacity();
        products[productCount] = p;
        hashTable.insert(&products[productCount]);
        productCount++;
        recommendationGraph.resize(productCount);
        if (productCount > 1) {
            recommendationGraph.addEdge(productCount - 2, productCount - 1);
        }
        rebuildBST();
    }

    void shellSort() {
        for (int gap = productCount / 2; gap > 0; gap /= 2) {
            for (int i = gap; i < productCount; i++) {
                Product temp = products[i];
                int j;
                for (j = i; j >= gap && products[j - gap].price > temp.price; j -= gap)
                    products[j] = products[j - gap];
                products[j] = temp;
            }
        }
        rebuildBST();
    }

    void mergeSortByPrice() {
        if (productCount > 0)
            mergeSort(products, 0, productCount - 1);
        rebuildBST();
    }

    Product* searchProductById(int id) {
        return hashTable.search(id);
    }

    Product* getProductArray() {
        return products;
    }

    int getProductCount() const {
        return productCount;
    }

    bool reduceStock(int productId, int quantity) {
        Product* p = searchProductById(productId);
        if (p && p->stock >= quantity) {
            p->stock -= quantity;
            return true;
        }
        return false;
    }
};

enum ScreenType {
    SCREEN_MAIN_MENU,
    SCREEN_PRODUCTS,
    SCREEN_CART,
    SCREEN_USERS,
    SCREEN_ORDERS,
    SCREEN_SEARCH
};

struct TextBox {
    Rectangle bounds;
    string text;
    bool active;
    int maxLen;
};

bool Button(Rectangle rec, const char* text) {
    Vector2 mouse = GetMousePosition();
    bool hover = CheckCollisionPointRec(mouse, rec);
    Color bg = hover ? Color{ 220, 230, 245, 255 } : Color{ 245, 247, 250, 255 };
    DrawRectangleRounded(rec, 0.3f, 8, bg);
    DrawRectangleRoundedLines(rec, 0.3f, 8, Color{ 60, 90, 140, 255 });
    int fontSize = 20;
    int textWidth = MeasureText(text, fontSize);
    DrawText(text, (int)(rec.x + (rec.width - textWidth) / 2), (int)(rec.y + (rec.height - fontSize) / 2), fontSize, Color{ 20, 30, 40, 255 });
    return hover && IsMouseButtonPressed(MOUSE_LEFT_BUTTON);
}

void DrawTextBox(TextBox& tb, bool numeric = false) {
    Vector2 mouse = GetMousePosition();
    bool hover = CheckCollisionPointRec(mouse, tb.bounds);
    if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
        tb.active = hover;
    }

    Color bg = tb.active ? Color{ 255, 255, 255, 255 } : Color{ 240, 240, 245, 255 };
    DrawRectangleRec(tb.bounds, bg);
    DrawRectangleLinesEx(tb.bounds, 2.0f,
        tb.active ? Color{ 30, 144, 255, 255 } : Color{ 150, 150, 160, 255 });

    int fontSize = 18;
    DrawText(tb.text.c_str(),
        (int)tb.bounds.x + 8,
        (int)(tb.bounds.y + (tb.bounds.height - fontSize) / 2),
        fontSize, Color{ 30, 30, 40, 255 });

    if (tb.active) {
        int key = GetCharPressed();
        while (key > 0) {
            if (key >= 32 && key <= 126) {
                if ((int)tb.text.size() < tb.maxLen) {
                    if (numeric) {
                        if ((key >= '0' && key <= '9') || key == '.' || key == '-') {
                            if (key == '.' && tb.text.find('.') != string::npos) {}
                            else if (key == '-' && !tb.text.empty()) {}
                            else { tb.text.push_back((char)key); }
                        }
                    }
                    else {
                        tb.text.push_back((char)key);
                    }
                }
            }
            key = GetCharPressed();
        }

        if (IsKeyPressed(KEY_BACKSPACE) && !tb.text.empty()) {
            tb.text.pop_back();
        }
    }
}

int main() {
    Admin admin(6, 2);
    admin.initializeProducts();

    SystemClass sys;

    sys.addUser("Alice");
    sys.addUser("Charlie");
    sys.addUser("Bob");

    string currentUser = "Alice";
    string actionMessage = "Current User: Alice. Select a screen to start shopping.";

    const int screenWidth = 1280;
    const int screenHeight = 720;
    InitWindow(screenWidth, screenHeight, "Smart Shopping System - DSA + GUI");
    SetTargetFPS(60);

    ScreenType currentScreen = SCREEN_MAIN_MENU;

    TextBox tbProdID = { Rectangle{900, 150, 150, 32}, "", false, 10 };
    TextBox tbProdName = { Rectangle{900, 200, 250, 32}, "", false, 20 };
    TextBox tbProdPrice = { Rectangle{900, 250, 150, 32}, "", false, 10 };
    TextBox tbProdStock = { Rectangle{900, 300, 150, 32}, "", false, 10 };

    TextBox tbUserName = { Rectangle{900, 180, 250, 32}, "", false, 20 };
    TextBox tbSelectUser = { Rectangle{900, 380, 250, 32}, "", false, 20 };

    TextBox tbOrderPrio = { Rectangle{900, 230, 150, 32}, "", false, 5 };

    TextBox tbSearchID = { Rectangle{900, 180, 150, 32}, "", false, 10 };
    string searchResult = "";

    string lastOrderMessage = "";
    string lastPriorityMessage = "";

    float scrollOffset = 0.0f;

    while (!WindowShouldClose()) {

        if (currentScreen == SCREEN_PRODUCTS || currentScreen == SCREEN_CART || currentScreen == SCREEN_USERS || currentScreen == SCREEN_ORDERS) {
            float wheel = GetMouseWheelMove();
            scrollOffset += wheel * 20.0f;
            if (scrollOffset > 0) scrollOffset = 0;
        }

        BeginDrawing();
        ClearBackground(Color{ 235, 240, 250, 255 });

        DrawRectangle(0, 0, screenWidth, 60, Color{ 30, 60, 120, 255 });
        DrawText("Smart Shopping System (DSA Demo)", 20, 18, 24, RAYWHITE);

        string userDisplay = "Logged In: " + currentUser;
        DrawText(userDisplay.c_str(), 500, 18, 20, RAYWHITE);

        if (currentScreen != SCREEN_MAIN_MENU) {
            Rectangle backBtn = { (float)screenWidth - 140.0f, 15.0f, 120.0f, 30.0f };
            if (Button(backBtn, "Main Menu")) {
                currentScreen = SCREEN_MAIN_MENU;
                scrollOffset = 0.0f;
            }
        }

        DrawText(actionMessage.c_str(), 20, screenHeight - 40, 18, Color{ 30, 60, 120, 255 });

        switch (currentScreen) {
        case SCREEN_MAIN_MENU: {
            DrawText("Main Menu", 580, 90, 30, Color{ 30, 30, 40, 255 });

            Rectangle btn1 = { screenWidth / 2.0f - 170, 160, 340, 60 };
            Rectangle btn2 = { screenWidth / 2.0f - 170, 240, 340, 60 };
            Rectangle btn3 = { screenWidth / 2.0f - 170, 320, 340, 60 };
            Rectangle btn4 = { screenWidth / 2.0f - 170, 400, 340, 60 };
            Rectangle btn5 = { screenWidth / 2.0f - 170, 480, 340, 60 };

            if (Button(btn1, "Products (View / Add / Sort)")) currentScreen = SCREEN_PRODUCTS;
            if (Button(btn2, "Customer Cart & History (List & Stack)")) currentScreen = SCREEN_CART;
            if (Button(btn3, "Users (AVL Tree View & Selection)")) currentScreen = SCREEN_USERS;
            if (Button(btn4, "Orders (FIFO Queue & Priority Queue)")) currentScreen = SCREEN_ORDERS;
            if (Button(btn5, "Search Product (Hash Table Lookup)")) currentScreen = SCREEN_SEARCH;
            break;
        }

        case SCREEN_PRODUCTS: {
            DrawText("Products & Sorting (Dynamic Array & Merge/Shell Sort)", 80, 80, 28, Color{ 30, 30, 40, 255 });

            Product* arr = admin.getProductArray();
            int n = admin.getProductCount();

            Rectangle shellBtn = { 80, 120, 200, 40 };
            Rectangle mergeBtn = { 300, 120, 200, 40 };

            if (Button(shellBtn, "Shell Sort by Price")) {
                admin.shellSort();
                actionMessage = "Products sorted using Shell Sort!";
            }
            if (Button(mergeBtn, "Merge Sort by Price")) {
                admin.mergeSortByPrice();
                actionMessage = "Products sorted using Merge Sort!";
            }

            DrawText("Existing Products (Click to sort or add to cart):", 80, 170, 22, Color{ 40, 40, 60, 255 });

            int startX = 80;
            int cardW = 420;
            int cardH = 80;
            int margin = 20;

            for (int i = 0; i < n; i++) {
                float x = (float)startX;
                float y = (float)(210 + i * (cardH + margin) + scrollOffset);

                if (y + cardH > 60 && y < screenHeight) {
                    Rectangle card = { x, y, (float)cardW, (float)cardH };
                    DrawRectangleRounded(card, 0.2f, 8, Color{ 250, 250, 255, 255 });
                    DrawRectangleRoundedLines(card, 0.2f, 8, Color{ 160, 160, 200, 255 });

                    string line1 = "ID: " + to_string(arr[i].id) + " | " + arr[i].name;
                    string line2 = "Price: $" + to_string(arr[i].price).substr(0, to_string(arr[i].price).find('.') + 3) + " | Stock: " + to_string(arr[i].stock);
                    DrawText(line1.c_str(), (int)x + 10, (int)y + 10, 18, Color{ 30, 30, 50, 255 });
                    DrawText(line2.c_str(), (int)x + 10, (int)y + 40, 16, Color{ 80, 80, 110, 255 });

                    Rectangle addBtn = { x + cardW - 140.0f, y + cardH - 32.0f, 130.0f, 26.0f };
                    if (Button(addBtn, "Add to Cart")) {
                        Customer* activeCart = sys.getUserCartData(currentUser);
                        if (activeCart && arr[i].stock > 0) {
                            activeCart->addToCart(arr[i]);
                            activeCart->pushRecent(arr[i]);
                            admin.reduceStock(arr[i].id, 1); // ADDED: Reduce stock
                            actionMessage = arr[i].name + " added to " + currentUser + "'s cart. Stock reduced to " + to_string(arr[i].stock);
                        }
                        else if (arr[i].stock == 0) {
                            actionMessage = "Out of stock!";
                        }
                        else {
                            actionMessage = "Error: Please select a user first.";
                        }
                    }
                }
            }

            DrawText("Add New Product", 900, 110, 22, Color{ 30, 30, 40, 255 });
            DrawText("ID:", 840, 157, 18, Color{ 30, 30, 40, 255 });
            DrawText("Name:", 840, 207, 18, Color{ 30, 30, 40, 255 });
            DrawText("Price:", 840, 257, 18, Color{ 30, 30, 40, 255 });
            DrawText("Stock:", 840, 307, 18, Color{ 30, 30, 40, 255 });
            DrawTextBox(tbProdID, true);
            DrawTextBox(tbProdName, false);
            DrawTextBox(tbProdPrice, true);
            DrawTextBox(tbProdStock, true);

            Rectangle addProdBtn = { 900, 360, 200, 40 };
            if (Button(addProdBtn, "Add Product")) {
                if (!tbProdID.text.empty() && !tbProdName.text.empty() &&
                    !tbProdPrice.text.empty() && !tbProdStock.text.empty()) {
                    try {
                        int id = stoi(tbProdID.text);
                        double price = stod(tbProdPrice.text);
                        int stock = stoi(tbProdStock.text);
                        if (id > 0 && price >= 0.0 && stock >= 0) {
                            Product p = { id, tbProdName.text, price, stock };
                            admin.addProduct(p);
                            actionMessage = "Product " + tbProdName.text + " added successfully!";
                            tbProdID.text.clear();
                            tbProdName.text.clear();
                            tbProdPrice.text.clear();
                            tbProdStock.text.clear();
                        }
                    }
                    catch (...) { actionMessage = "Invalid input!"; }
                }
            }
            break;
        }

        case SCREEN_CART: {
            Customer* activeCart = sys.getUserCartData(currentUser);

            DrawText(("Customer Cart (Linked List) for " + currentUser).c_str(), 80, 80, 28, Color{ 30, 30, 40, 255 });

            if (activeCart) {
                vector<Product> items = activeCart->getCartItems();

                // ========== CHECKOUT OPTIONS AT THE TOP ==========
                if (!items.empty()) {
                    DrawRectangle(40, 115, 1200, 165, Color{ 250, 250, 255, 255 });
                    DrawRectangleLines(40, 115, 1200, 165, Color{ 100, 120, 180, 255 });

                    DrawText("Checkout Options:", 60, 125, 20, Color{ 40, 40, 60, 255 });

                    // FIFO Checkout
                    DrawText("Standard Queue:", 60, 155, 18, Color{ 60, 60, 80, 255 });
                    Rectangle checkoutFIFO = { 60, 180, 200, 50 };
                    if (Button(checkoutFIFO, "Checkout (FIFO)")) {
                        int orderID = sys.enqueueOrder(currentUser, items);
                        activeCart->clearCartAfterCheckout();
                        actionMessage = "Order #" + to_string(orderID) + " placed in FIFO queue for " + currentUser;
                        lastOrderMessage = "Order #" + to_string(orderID) + " for " + currentUser;
                    }
                    DrawText("First-come, first-served", 60, 238, 14, Color{ 100, 100, 120, 255 });

                    DrawLine(300, 125, 300, 270, Color{ 150, 150, 180, 255 });

                    // Priority Checkout
                    DrawText("Priority Queue:", 340, 125, 20, Color{ 40, 40, 60, 255 });
                    DrawText("Select Priority Level:", 340, 155, 18, Color{ 60, 60, 80, 255 });

                    Rectangle prio1Btn = { 340, 185, 70, 45 };
                    Rectangle prio2Btn = { 420, 185, 70, 45 };
                    Rectangle prio3Btn = { 500, 185, 70, 45 };
                    Rectangle prio4Btn = { 580, 185, 70, 45 };

                    static int selectedPriority = 2;

                    Color prioColors[] = {
                        Color{ 255, 180, 180, 255 },
                        Color{ 255, 220, 180, 255 },
                        Color{ 255, 255, 180, 255 },
                        Color{ 200, 255, 200, 255 }
                    };
                    Color prioBorderColors[] = {
                        Color{ 220, 0, 0, 255 },
                        Color{ 220, 100, 0, 255 },
                        Color{ 200, 150, 0, 255 },
                        Color{ 0, 150, 0, 255 }
                    };
                    const char* prioLabels[] = { "URGENT", "HIGH", "MEDIUM", "LOW" };

                    Rectangle prioBtns[] = { prio1Btn, prio2Btn, prio3Btn, prio4Btn };
                    for (int i = 0; i < 4; i++) {
                        bool isSelected = (selectedPriority == i + 1);
                        DrawRectangleRounded(prioBtns[i], 0.2f, 8, prioColors[i]);
                        DrawRectangleRoundedLines(prioBtns[i], 0.2f, 8,
                            isSelected ? Color{ 0, 0, 0, 255 } : prioBorderColors[i]);
                        if (isSelected) {
                            DrawRectangleLinesEx(prioBtns[i], 3.0f, Color{ 0, 0, 0, 255 });
                        }

                        string numStr = to_string(i + 1);
                        DrawText(numStr.c_str(),
                            (int)(prioBtns[i].x + prioBtns[i].width / 2 - 8),
                            (int)(prioBtns[i].y + 8), 24, Color{ 0, 0, 0, 255 });
                        DrawText(prioLabels[i],
                            (int)(prioBtns[i].x + 5),
                            (int)(prioBtns[i].y + 30), 11, Color{ 40, 40, 40, 255 });

                        Vector2 mouse = GetMousePosition();
                        if (CheckCollisionPointRec(mouse, prioBtns[i]) && IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
                            selectedPriority = i + 1;
                        }
                    }

                    Rectangle checkoutPriority = { 680, 185, 250, 45 };
                    if (Button(checkoutPriority, "Checkout with Priority")) {
                        sys.enqueuePriorityOrder(currentUser, items, selectedPriority);
                        activeCart->clearCartAfterCheckout();
                        actionMessage = "Priority order (" + string(prioLabels[selectedPriority - 1]) +
                            ") placed for " + currentUser;
                    }

                    string prioText = "Selected: " + string(prioLabels[selectedPriority - 1]);
                    DrawText(prioText.c_str(), 680, 240, 16, prioBorderColors[selectedPriority - 1]);
                }

                // ========== CART ITEMS BELOW CHECKOUT (DISPLAYED ONLY ONCE) ==========
                int cartStartY = 300;
                DrawText("Items in Cart:", 80, cartStartY, 22, Color{ 40, 40, 60, 255 });

                if (items.empty()) {
                    DrawText("Cart is empty.", 80, cartStartY + 40, 24, Color{ 100, 100, 120, 255 });
                }
                else {
                    int boxW = 260;
                    int boxH = 70;
                    int rowItems = (screenWidth - 160) / (boxW + 40);

                    for (size_t i = 0; i < items.size(); i++) {
                        int col = i % rowItems;
                        int row = i / rowItems;

                        int x = 80 + col * (boxW + 40);
                        int y = cartStartY + 40 + row * (boxH + 20) + (int)scrollOffset;

                        if (y + boxH > cartStartY && y < screenHeight - 200) {
                            Rectangle box = { (float)x, (float)y, (float)boxW, (float)boxH };
                            DrawRectangleRounded(box, 0.25f, 8, Color{ 250, 245, 225, 255 });
                            DrawRectangleRoundedLines(box, 0.25f, 8, Color{ 180, 140, 80, 255 });

                            string t1 = items[i].name;
                            string t2 = "Price: $" + to_string(items[i].price).substr(0, to_string(items[i].price).find('.') + 3);
                            DrawText(t1.c_str(), x + 10, y + 10, 18, Color{ 40, 30, 20, 255 });
                            DrawText(t2.c_str(), x + 10, y + 35, 16, Color{ 90, 60, 30, 255 });
                        }
                    }
                }

                // ========== RECENT VIEWS SECTION (UNCHANGED) ==========
                DrawText("Recent Views (Stack - LIFO)", 80, screenHeight - 280, 28, Color{ 30, 30, 40, 255 });
                vector<Product> recent = activeCart->getRecentViews();
                if (recent.empty()) {
                    DrawText("No recent views.", 80, screenHeight - 240, 24, Color{ 100, 100, 120, 255 });
                }
                else {
                    int x = 80;
                    int y = screenHeight - 230;
                    int boxW = 180;
                    int boxH = 60;

                    DrawText("Top:", x - 40, y + 20, 16, Color{ 255, 0, 0, 255 });

                    for (size_t i = 0; i < recent.size() && i < 5; i++) {
                        Rectangle box = { (float)x, (float)y, (float)boxW, (float)boxH };
                        DrawRectangleRounded(box, 0.25f, 8, Color{ 240, 255, 240, 255 });
                        DrawRectangleRoundedLines(box, 0.25f, 8, Color{ 80, 180, 80, 255 });

                        string t1 = recent[i].name;
                        string t2 = "ID: " + to_string(recent[i].id);
                        DrawText(t1.c_str(), x + 10, y + 8, 16, Color{ 20, 40, 20, 255 });
                        DrawText(t2.c_str(), x + 10, y + 32, 14, Color{ 50, 100, 50, 255 });

                        x += boxW + 20;
                        if (i == 0) DrawText("->", x - 10, y + 20, 20, Color{ 80, 80, 80, 255 });
                    }
                }
            }
            else {
                DrawText("User not logged in or data error.", 80, 140, 24, Color{ 150, 50, 50, 255 });
            }
            break;
        }

        case SCREEN_USERS: {
            DrawText("User Accounts (AVL Tree) & Selection", 80, 80, 28, Color{ 30, 30, 40, 255 });

            DrawText("Add New User:", 900, 130, 22, Color{ 30, 30, 40, 255 });
            DrawText("Name:", 840, 187, 18, Color{ 30, 30, 40, 255 });
            DrawTextBox(tbUserName, false);
            Rectangle addUserBtn = { 900, 240, 200, 40 };
            if (Button(addUserBtn, "Add User")) {
                if (!tbUserName.text.empty()) {
                    sys.addUser(tbUserName.text);
                    actionMessage = "User " + tbUserName.text + " added to system.";
                    tbUserName.text.clear();
                }
            }

            DrawText("Select Active User:", 900, 340, 22, Color{ 30, 30, 40, 255 });
            DrawTextBox(tbSelectUser, false);
            Rectangle selectUserBtn = { 900, 430, 200, 40 };

            if (Button(selectUserBtn, "Set Active User")) {
                if (!tbSelectUser.text.empty()) {
                    if (sys.getUserCartData(tbSelectUser.text)) {
                        currentUser = tbSelectUser.text;
                        actionMessage = "Switched to user: " + currentUser;
                        tbSelectUser.text.clear();
                    }
                    else {
                        actionMessage = "Error: User '" + tbSelectUser.text + "' not found.";
                    }
                }
            }

            DrawText("Existing Users (Alphabetical Inorder Traversal):", 80, 140, 22, Color{ 40, 40, 60, 255 });
            vector<string> users = sys.getUsersInOrder();

            int x = 80;
            int y = 180 + (int)scrollOffset;
            int cardW = 200;
            int cardH = 50;
            int margin = 15;
            int colCount = 3;

            for (size_t i = 0; i < users.size(); i++) {
                int col = i % colCount;
                int row = i / colCount;

                x = 80 + col * (cardW + margin * 2);
                y = 180 + row * (cardH + margin) + (int)scrollOffset;

                Color boxColor = (users[i] == currentUser) ? Color{ 200, 255, 200, 255 } : Color{ 255, 255, 200, 255 };
                Color lineColor = (users[i] == currentUser) ? Color{ 80, 180, 80, 255 } : Color{ 180, 180, 100, 255 };

                if (y + cardH > 60 && y < screenHeight) {
                    Rectangle box = { (float)x, (float)y, (float)cardW, (float)cardH };
                    DrawRectangleRounded(box, 0.2f, 8, boxColor);
                    DrawRectangleRoundedLines(box, 0.2f, 8, lineColor);

                    DrawText(users[i].c_str(), x + 10, y + 15, 18, Color{ 40, 40, 20, 255 });
                }
            }
            break;
        }

        case SCREEN_ORDERS: {
            DrawText("Order Processing Systems", 480, 80, 30, Color{ 30, 30, 40, 255 });

            // ========== LEFT SIDE: FIFO QUEUE (First-In-First-Out) ==========
            DrawRectangle(40, 110, 580, 580, Color{ 240, 245, 255, 255 });
            DrawRectangleLines(40, 110, 580, 580, Color{ 100, 120, 180, 255 });

            DrawText("FIFO Queue (Linked List)", 80, 130, 24, Color{ 30, 60, 120, 255 });
            DrawText("First-In-First-Out: Orders processed in arrival order", 80, 160, 16, Color{ 80, 80, 100, 255 });

            Rectangle procFIFOBtn = { 80, 190, 200, 40 };
            if (Button(procFIFOBtn, "Process Front Order")) {
                OrderInfo processed;
                if (sys.dequeueOrderOnce(processed)) {
                    lastOrderMessage = "? Processed Order #" + to_string(processed.orderID) + " (" + processed.userName + ")";
                }
                else {
                    lastOrderMessage = "Queue is empty!";
                }
            }

            if (!lastOrderMessage.empty()) {
                DrawRectangle(80, 240, 500, 40, Color{ 220, 255, 220, 255 });
                DrawRectangleLines(80, 240, 500, 40, Color{ 80, 180, 80, 255 });
                DrawText(lastOrderMessage.c_str(), 90, 250, 18, Color{ 0, 100, 0, 255 });
            }

            DrawText("Current FIFO Queue:", 80, 300, 20, Color{ 40, 40, 60, 255 });
            DrawText("FRONT ?", 80, 330, 16, Color{ 200, 0, 0, 255 });
            DrawText("? REAR", 500, 330, 16, Color{ 0, 150, 0, 255 });

            vector<OrderInfo> fifoOrders = sys.getQueueSnapshot();
            if (fifoOrders.empty()) {
                DrawText("No orders in FIFO queue", 80, 360, 18, Color{ 120, 120, 140, 255 });
            }
            else {
                int x = 80;
                int y = 360;
                for (size_t i = 0; i < fifoOrders.size(); i++) {
                    // Color coding: Front order is red (next to process)
                    Color boxColor = (i == 0) ? Color{ 255, 200, 200, 255 } : Color{ 200, 220, 255, 255 };
                    Color borderColor = (i == 0) ? Color{ 200, 0, 0, 255 } : Color{ 80, 100, 200, 255 };

                    if (y + 90 > 680) break; // Don't overflow

                    DrawRectangleRounded(Rectangle{ (float)x, (float)y, 500, 80 }, 0.2f, 8, boxColor);
                    DrawRectangleRoundedLines(Rectangle{ (float)x, (float)y, 500, 80 }, 0.2f, 8, borderColor);

                    string posLabel = (i == 0) ? "[FRONT - Next to Process]" : "[Position " + to_string(i + 1) + "]";
                    DrawText(posLabel.c_str(), x + 10, y + 8, 14, Color{ 100, 0, 0, 255 });

                    string orderInfo = "Order #" + to_string(fifoOrders[i].orderID);
                    string userInfo = "User: " + fifoOrders[i].userName;
                    string itemInfo = "Items: " + to_string(fifoOrders[i].items.size());

                    DrawText(orderInfo.c_str(), x + 10, y + 28, 18, Color{ 20, 20, 60, 255 });
                    DrawText(userInfo.c_str(), x + 10, y + 48, 16, Color{ 60, 60, 100, 255 });
                    DrawText(itemInfo.c_str(), x + 10, y + 65, 14, Color{ 80, 80, 120, 255 });

                    y += 90;

                    // Draw arrow between orders
                    if (i < fifoOrders.size() - 1 && y + 90 <= 680) {
                        DrawText("?", x + 250, y - 12, 20, Color{ 100, 100, 100, 255 });
                    }
                }
            }

            // ========== RIGHT SIDE: PRIORITY QUEUE (Min-Heap) ==========
            DrawRectangle(660, 110, 580, 580, Color{ 255, 245, 240, 255 });
            DrawRectangleLines(660, 110, 580, 580, Color{ 180, 100, 80, 255 });

            DrawText("Priority Queue (Min-Heap)", 700, 130, 24, Color{ 150, 50, 30, 255 });
            DrawText("Lower priority number = Higher urgency (1 = Highest)", 700, 160, 16, Color{ 100, 80, 80, 255 });

            Rectangle procPrioBtn = { 700, 190, 220, 40 };
            if (Button(procPrioBtn, "Process Highest Priority")) {
                OrderInfo processed;
                if (sys.processOnePriorityOrder(processed)) {
                    lastPriorityMessage = "? Processed Order #" + to_string(processed.orderID) +
                        " (" + processed.userName + ") Priority: " + to_string(processed.priority);
                }
                else {
                    lastPriorityMessage = "Priority queue is empty!";
                }
            }

            if (!lastPriorityMessage.empty()) {
                DrawRectangle(700, 240, 500, 40, Color{ 255, 220, 220, 255 });
                DrawRectangleLines(700, 240, 500, 40, Color{ 180, 80, 80, 255 });
                DrawText(lastPriorityMessage.c_str(), 710, 250, 16, Color{ 150, 0, 0, 255 });
            }

            DrawText("Current Priority Queue (Top to Bottom):", 700, 300, 20, Color{ 40, 40, 60, 255 });
            DrawText("Priority Scale: 1=Urgent, 2=High, 3=Medium, 4+=Low", 700, 325, 14, Color{ 100, 80, 80, 255 });

            vector<OrderInfo> prioOrders = sys.getPriorityOrdersSnapshot();
            if (prioOrders.empty()) {
                DrawText("No orders in priority queue", 700, 360, 18, Color{ 120, 120, 140, 255 });
            }
            else {
                int x = 700;
                int y = 360;

                for (size_t i = 0; i < prioOrders.size(); i++) {
                    if (y + 90 > 680) break;

                    // Color coding based on priority: 1=Red (urgent), 2=Orange, 3=Yellow, 4+=Green
                    Color boxColor;
                    Color borderColor;
                    string priorityLabel;

                    if (prioOrders[i].priority == 1) {
                        boxColor = Color{ 255, 180, 180, 255 };
                        borderColor = Color{ 220, 0, 0, 255 };
                        priorityLabel = "URGENT";
                    }
                    else if (prioOrders[i].priority == 2) {
                        boxColor = Color{ 255, 220, 180, 255 };
                        borderColor = Color{ 220, 100, 0, 255 };
                        priorityLabel = "HIGH";
                    }
                    else if (prioOrders[i].priority == 3) {
                        boxColor = Color{ 255, 255, 180, 255 };
                        borderColor = Color{ 200, 150, 0, 255 };
                        priorityLabel = "MEDIUM";
                    }
                    else {
                        boxColor = Color{ 200, 255, 200, 255 };
                        borderColor = Color{ 0, 150, 0, 255 };
                        priorityLabel = "LOW";
                    }

                    DrawRectangleRounded(Rectangle{ (float)x, (float)y, 500, 80 }, 0.2f, 8, boxColor);
                    DrawRectangleRoundedLines(Rectangle{ (float)x, (float)y, 500, 80 }, 0.2f, 8, borderColor);

                    string posLabel = (i == 0) ? "[TOP - Next to Process]" : "[Heap Position " + to_string(i + 1) + "]";
                    DrawText(posLabel.c_str(), x + 10, y + 8, 14, Color{ 150, 0, 0, 255 });

                    string orderInfo = "Order #" + to_string(prioOrders[i].orderID);
                    string userInfo = "User: " + prioOrders[i].userName;
                    string prioInfo = "Priority: " + to_string(prioOrders[i].priority) + " (" + priorityLabel + ")";

                    DrawText(orderInfo.c_str(), x + 10, y + 28, 18, Color{ 60, 20, 20, 255 });
                    DrawText(userInfo.c_str(), x + 10, y + 48, 16, Color{ 100, 60, 60, 255 });
                    DrawText(prioInfo.c_str(), x + 10, y + 65, 14, borderColor);

                    y += 90;

                    if (i < prioOrders.size() - 1 && y + 90 <= 680) {
                        DrawText("?", x + 250, y - 12, 20, Color{ 100, 100, 100, 255 });
                    }
                }
            }

            break;
        }

        case SCREEN_SEARCH: {
            DrawText("Product Search (Hash Table)", 80, 80, 28, Color{ 30, 30, 40, 255 });
            DrawText("Enter Product ID:", 80, 150, 22, Color{ 30, 30, 40, 255 });
            DrawTextBox(tbSearchID, true);
            Rectangle searchBtn = { 500, 150, 150, 32 };
            if (Button(searchBtn, "Search")) {
                searchResult = "";
                if (!tbSearchID.text.empty()) {
                    try {
                        int id = stoi(tbSearchID.text);
                        Product* p = admin.searchProductById(id);
                        if (p) {
                            searchResult = "Found! ID: " + to_string(p->id) + " | Name: " + p->name +
                                " | Price: $" + to_string(p->price).substr(0, to_string(p->price).find('.') + 3) +
                                " | Stock: " + to_string(p->stock);
                        }
                        else {
                            searchResult = "Product with ID " + to_string(id) + " not found.";
                        }
                    }
                    catch (...) {
                        searchResult = "Invalid ID format entered.";
                    }
                }
            }
            DrawText("Search Result:", 80, 250, 22, Color{ 30, 30, 40, 255 });
            DrawText(searchResult.c_str(), 80, 290, 20, Color{ 10, 10, 20, 255 });
            break;
        }

        default: break;
        }

        EndDrawing();
    }

    CloseWindow();
    return 0;
}
