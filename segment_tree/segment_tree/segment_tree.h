#pragma once

#include <vector>
#include <cmath>

int INF = 1e9;

class segmentTree {
private:
public:
    // Функция build_tree(V) превращает массив V в дерево отрезков для этого массива. 
    // Построим дерево, пробежавшись по элементам с (n – 1)-ого по первый, считая минимум значений в сыновьях для каждой вершины.
    void build_tree(std::vector<int>& V) {
        // Размер, доведенный до степени двойки.
        int n = V.size();
        n = (1 << int(log2(n - 1) + 1));
        V.resize(2 * n, INF);
        
        // Инициализируем листы
        for (int i = n; i < 2 * n; i++) {
            V[i] = V[i - n];
        }
        // и все остальные вершины
        for (int i = n - 1; i > 0; i--) {
            V[i] = std::min(V[2 * i], V[2 * i + 1]);
        }
    }

    // Поиск минимума на заданном отрезке [l, r]
    int rmq_up(std::vector<int>& T, int l, int r) {
        int ans = INF;
        int n = T.size()/2;
        l += n;
        r += n;
        // Продолжаем операции, пока указатели не зайдут один за другой.
        while (l <= r) {
            // Если l - правый сын своего родителя, учитываем его фундаментальный отрезок
            if (l & 1) {
                ans = std::min(ans, T[l]);
            }
            // Если r - левый сын своего родителя, учитываем его фундаментальный отрезок
            if (!(r & 1)) {
                ans = std::min(ans, T[r]);
            }
            // Сдвигаем указатели на уровень выше.
            l = (l + 1)/2;
            r = (r - 1)/2;
        }
        return ans;
    }
    
    // При изменении элемента достаточно просто пробежаться от его листа до корня и обновить значение во всех вершинах на пути по формуле T[i] = min(T[2i], T[2i + 1]).
    void update(std::vector<int>& T, int i, int x) {
        int n = T.size() / 2;
        i += n; 
        T[i] = x;
        while (i > 1) {
            i /= 2;
            T[i] = std::min(T[2 * i], T[2 * i + 1]);
        }
    }
};

