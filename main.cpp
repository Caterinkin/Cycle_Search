#include <iostream>
#include <fstream>
#include <vector>

// Функция для поиска циклов с использованием DFS
bool hasCycleDFS(int vertex, int parent, const std::vector<std::vector<int>>& adjacencyMatrix, std::vector<bool>& visited)
{
    // Помечаем текущую вершину как посещённую
    visited[vertex] = true;

    // Обходим все смежные вершины
    for (int i = 0; i < adjacencyMatrix.size(); ++i)
    {
        if (adjacencyMatrix[vertex][i] == 1)
        {
            if (!visited[i])
            {
                // Рекурсивно вызываем DFS для смежной вершины
                if (hasCycleDFS(i, vertex, adjacencyMatrix, visited))
                {
                    return true; // Найден цикл
                }
            }
            else if (i != parent)
            {
                // Если вершина уже посещена и не является родительской, то это цикл
                return true;
            }
        }
    }
    // Цикл не найден
    return false;
}

// Функция для проверки наличия цикла в графе
bool hasCycle(const std::vector<std::vector<int>>& adjacencyMatrix)
{
    int N = adjacencyMatrix.size();
    std::vector<bool> visited(N, false); // Массив для хранения информации о посещённых вершинах

    // Проверяем наличие цикла для каждой вершины
    for (int i = 0; i < N; ++i)
    {
        if (!visited[i])
        {
            if (hasCycleDFS(i, -1, adjacencyMatrix, visited))
            {
                return true; // Найден цикл
            }
        }
    }

    // Цикл не найден
    return false;
}

int main()
{
    setlocale(LC_ALL, "rus");
    
    std::ifstream inputFile("input.txt");
    if (!inputFile.is_open())
    {
        std::cerr << "Ошибка открытия файла!" << std::endl;
        return 1; // Возвращаем 1 в случае ошибки
    }

    // Читаем количество вершин графа
    int N;
    inputFile >> N;

    // Создаём матрицу смежности
    std::vector<std::vector<int>> adjacencyMatrix(N, std::vector<int>(N));

    // Заполняем матрицу смежности из файла
    for (int i = 0; i < N; ++i)
    {
        for (int j = 0; j < N; ++j)
        {
            inputFile >> adjacencyMatrix[i][j];
        }
    }

    inputFile.close();

    // Проверяем наличие цикла в графе
    if (hasCycle(adjacencyMatrix))
    {
        std::cout << "В графе есть цикл!" << std::endl;
    }
    else
    {
        std::cout << "В графе нет циклов" << std::endl;
    }

    return EXIT_SUCCESS; 
}
