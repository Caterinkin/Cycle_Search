#include <iostream>
#include <fstream>
#include <vector>

// ������� ��� ������ ������ � �������������� DFS
bool hasCycleDFS(int vertex, int parent, const std::vector<std::vector<int>>& adjacencyMatrix, std::vector<bool>& visited)
{
    // �������� ������� ������� ��� ����������
    visited[vertex] = true;

    // ������� ��� ������� �������
    for (int i = 0; i < adjacencyMatrix.size(); ++i)
    {
        if (adjacencyMatrix[vertex][i] == 1)
        {
            if (!visited[i])
            {
                // ���������� �������� DFS ��� ������� �������
                if (hasCycleDFS(i, vertex, adjacencyMatrix, visited))
                {
                    return true; // ������ ����
                }
            }
            else if (i != parent)
            {
                // ���� ������� ��� �������� � �� �������� ������������, �� ��� ����
                return true;
            }
        }
    }
    // ���� �� ������
    return false;
}

// ������� ��� �������� ������� ����� � �����
bool hasCycle(const std::vector<std::vector<int>>& adjacencyMatrix)
{
    int N = adjacencyMatrix.size();
    std::vector<bool> visited(N, false); // ������ ��� �������� ���������� � ���������� ��������

    // ��������� ������� ����� ��� ������ �������
    for (int i = 0; i < N; ++i)
    {
        if (!visited[i])
        {
            if (hasCycleDFS(i, -1, adjacencyMatrix, visited))
            {
                return true; // ������ ����
            }
        }
    }

    // ���� �� ������
    return false;
}

int main()
{
    setlocale(LC_ALL, "rus");
    
    std::ifstream inputFile("input.txt");
    if (!inputFile.is_open())
    {
        std::cerr << "������ �������� �����!" << std::endl;
        return 1; // ���������� 1 � ������ ������
    }

    // ������ ���������� ������ �����
    int N;
    inputFile >> N;

    // ������ ������� ���������
    std::vector<std::vector<int>> adjacencyMatrix(N, std::vector<int>(N));

    // ��������� ������� ��������� �� �����
    for (int i = 0; i < N; ++i)
    {
        for (int j = 0; j < N; ++j)
        {
            inputFile >> adjacencyMatrix[i][j];
        }
    }

    inputFile.close();

    // ��������� ������� ����� � �����
    if (hasCycle(adjacencyMatrix))
    {
        std::cout << "� ����� ���� ����!" << std::endl;
    }
    else
    {
        std::cout << "� ����� ��� ������" << std::endl;
    }

    return EXIT_SUCCESS; 
}