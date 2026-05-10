#include <iostream>
#include <fstream>

using namespace std;

class Graph {

    int city;
    int arr[10][10];
    char name[10];

    // ADDED FOR COMPARISON 
    int greedyCost = 0;
    int bruteCost = 0;

    //  ADDED FOR MEMORY USAGE 
    int greedyMemory = 0;
    int bruteMemory = 0;

    int bestPath[10];

public:

    
    void createdatabase() {

        ofstream file("cities.txt");

        cout << endl << "Cities: ";
        cin >> city;

        file << city << endl;

        for (int i = 0; i < city; i++) {

            cout << "Name " << i + 1 << ": ";
            cin >> name[i];

            file << name[i] << " ";
        }

        file << endl;

        cout << endl << "Enter distances" << endl;

        for (int i = 0; i < city; i++) {

            for (int j = 0; j < city; j++) {

                cout << name[i] << " to " << name[j] << ": ";
                cin >> arr[i][j];

                file << arr[i][j] << " ";
            }

            file << endl;
        }

        file.close();

        cout << endl << "Data Saved" << endl;
    }

    void load() {

        ifstream file("cities.txt");

        if (!file) {

            cout << endl << "File Missing" << endl;
            return;
        }

        file >> city;

        for (int i = 0; i < city; i++) {
            file >> name[i];
        }

        for (int i = 0; i < city; i++) {

            for (int j = 0; j < city; j++) {
                file >> arr[i][j];
            }
        }

        file.close();

        cout << endl << "Data Loaded" << endl;
    }

    
    void display() {

        cout << endl;

        for (int i = 0; i < city; i++) {
            cout << "\t" << name[i];
        }

        cout << endl;

        for (int i = 0; i < city; i++) {

            cout << name[i];

            for (int j = 0; j < city; j++) {
                cout << "\t" << arr[i][j];
            }

            cout << endl;
        }
    }

    
    void greedy() {

        bool visited[10] = { false };

        int current = 0;
        int cost = 0;

        visited[0] = true;

        cout << endl << "Path: " << name[0];

        for (int i = 0; i < city - 1; i++) {

            int mincost = 999;
            int next = -1;

            for (int j = 0; j < city; j++) {

                if (!visited[j] && arr[current][j] != 0) {

                    if (arr[current][j] < mincost) {

                        mincost = arr[current][j];
                        next = j;
                    }
                }
            }

            visited[next] = true;

            cout << " -> " << name[next];

            cost += mincost;

            current = next;
        }

        cost += arr[current][0];

        cout << " -> " << name[0];

        cout << endl << "Total Cost = " << cost << endl;

        //  STORE GREEDY COST 
        greedyCost = cost;
    }

    
    void tsp(int start, int current, bool visited[],
        int count, int cost, int& mincost, int path[]) {

        path[count - 1] = current;

        if (count == city) {

            int totalCost = cost + arr[current][start];

            if (totalCost < mincost) {

                mincost = totalCost;

                //  STORE BEST PATH
                for (int i = 0; i < city; i++) {
                    bestPath[i] = path[i];
                }
            }

            return;
        }

        for (int i = 0; i < city; i++) {

            if (!visited[i] && arr[current][i] != 0) {

                visited[i] = true;

                path[count] = i;

                tsp(start, i, visited, count + 1,
                    cost + arr[current][i], mincost, path);

                visited[i] = false;
            }
        }
    }

    
    void bruteforcebetter() {

        bool visited[10] = { false };

        int mincost = 999;

        int path[10];

        visited[0] = true;

        path[0] = 0;

        tsp(0, 0, visited, 1, 0, mincost, path);

        cout << endl << "Best Cost = " << mincost << endl;

       
        bruteCost = mincost;

        
        cout << "Best Path: ";

        for (int i = 0; i < city; i++) {
            cout << name[bestPath[i]] << " -> ";
        }

        cout << name[0] << endl;
    }

   
    void memoryUsage() {

   
        int matrixMemory = city * city * sizeof(int);

       
        greedyMemory = matrixMemory
            + city * sizeof(bool);

        
        bruteMemory = matrixMemory
            + city * sizeof(bool)
            + city * sizeof(int);

        cout << endl << "===== MEMORY USAGE =====" << endl;

        cout << "Greedy Memory: "
            << greedyMemory << " bytes" << endl;

        cout << "Brute Force Memory: "
            << bruteMemory << " bytes" << endl;
    }

   
    long long factorial(int n) {
        long long result = 1;
        for (int i = 2; i <= n; i++) {
            result *= i;
        }
        return result;
    }

    
    void timeComplexity() {
        cout << endl << "===== TIME COMPLEXITY =====" << endl;
        cout << "Greedy Algorithm: O(n²) = " << (city * city) << " operations" << endl;
        cout << "Brute Force: O(n!) = " << factorial(city) << " operations" << endl;
    }

    
    void compareAlgorithms() {

        cout << endl << "===== ALGORITHM COMPARISON =====" << endl;

       
        timeComplexity();

       
        cout << endl << "Greedy Algorithm:" << endl;
        cout << "Cost: " << greedyCost << endl;
        cout << "Memory: " << greedyMemory << " bytes" << endl;
        cout << "Accuracy: Medium (Approximate Solution)" << endl;
        cout << "Speed: Fast" << endl;

        
        cout << endl << "Brute Force Algorithm:" << endl;
        cout << "Cost: " << bruteCost << endl;
        cout << "Memory: " << bruteMemory << " bytes" << endl;
        cout << "Accuracy: High (Optimal Solution)" << endl;
        cout << "Speed: Slow" << endl;

        cout << endl << "===== FINAL RESULT =====" << endl;

        
        if (greedyCost < bruteCost)
            cout << "Greedy gave better cost" << endl;
        else if (greedyCost > bruteCost)
            cout << "Brute Force gave better cost" << endl;
        else
            cout << "Both algorithms found same cost" << endl;

        
        if (greedyMemory < bruteMemory)
            cout << "Greedy uses less memory" << endl;
        else
            cout << "Brute Force uses less memory" << endl;

        cout << "===================================" << endl;
    }
};

int main() {

    Graph g;

    int choice;

    do {

        cout << endl << "1. Create";
        cout << endl << "2. Load";
        cout << endl << "3. Display";
        cout << endl << "4. Greedy";
        cout << endl << "5. Brute Force";
        cout << endl << "6. Memory Usage";
        cout << endl << "7. Compare";
        cout << endl << "0. Exit";

        cout << endl << "Choice: ";
        cin >> choice;

        switch (choice) {

        case 1:
            g.createdatabase();
            break;

        case 2:
            g.load();
            break;

        case 3:
            g.display();
            break;

        case 4:
            g.greedy();
            break;

        case 5:
            g.bruteforcebetter();
            break;

        case 6:
            g.memoryUsage();
            break;

        case 7:
            g.compareAlgorithms();
            break;

        case 0:
            cout << endl << "Program End" << endl;
            break;

        default:
            cout << endl << "Wrong Choice" << endl;
        }

    } while (choice != 0);

    return 0;
}