void bubble_sort(int A[], int N);
void select_sort(int A[], int N);
void inserting_sort(int A[], int N);
void qsort(int A[], int left, int right);
void swap(int A[], int i, int j);

void bubble_sort(int A[], int N)
{
    for (int i = 0; i < N-1; i++) {
        for (int j = 0; j < N-1-i; j++) {
            if (A[j] > A[j+1]) {
                swap(A, j, j+1);
            }
        }
    }
}

void select_sort(int A[], int N)
{
    for(int i = N-1; i > 0; i--) {
        int max_index = 0;
        for (int j = 1; j <= i; j++) {
            if (A[j] > A[max_index]) {
                max_index = j;
            }
        }
        swap(A, max_index, i);
    }
}

void inserting_sort(int A[], int N)
{
    for (int i = 1; i < N; i++) {
        int temp = A[i];
        for (int j = i; j > 0; j--) {
            if (A[j-1] > temp) {
                A[j] = A[j-1];
            } else {
                A[j] = temp;
                break;
            }
        }
        if (temp < A[0]) {
            A[0] = temp;
        }
    }
}

void qsort(int A[], int left, int right)
{
    int split_point = left;
    if (left >= right) {
        return;
    }
    int pivot = A[left];
    for (int i = left+1; i <= right; i++) {
        if (A[i] < pivot) {
            split_point++;
            swap(A, split_point, i);
        }
    }
    swap(A, left, split_point);
    qsort(A, left, split_point-1);
    qsort(A, split_point+1, right);

}



void swap(int A[], int i, int j)
{
    int tmp;
    tmp = A[i];
    A[i] = A[j];
    A[j] = tmp;
}
