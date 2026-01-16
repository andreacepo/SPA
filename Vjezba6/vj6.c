#include <stdio.h>
#include <stdlib.h>

#define MAX_N 10000

typedef struct {
	void* ignore;
	int priority;
} Element;

typedef struct {
	Element array[MAX_N];
	int size;
} PrioritetniRed;


void swap_elements(Element* arr, int i, int j) {
	Element temp = arr[i];
	arr[i] = arr[j];
	arr[j] = temp;
}


void sift_up_iter(Element* arr, int index) {
	int child = index;
	while (child > 0) {
		int parent = (child - 1) / 2;//formula za indeks roditelja u binarnoj gomili predstavljanoj nizom
		if (arr[child].priority > arr[parent].priority) {
			swap_elements(arr, child, parent);
			child = parent;
		}
		else {
			break;
		}
	}
}

//Ako je njegov prioritet veci od roditelja, treba “popeti” element prema gore dok ne sjedne na pravo mjesto.
void sift_up_rec(Element* arr, int index) {
	if (index == 0) return;
	int parent = (index - 1) / 2;
	if (arr[index].priority > arr[parent].priority) {
		swap_elements(arr, index, parent);
		sift_up_rec(arr, parent);
	}
}

void sift_down_iter(Element* arr, int current_index, int heap_size) {
	int parent = current_index;
	while (1) {
		//Racunamo indekse djece
		int left_child = 2 * parent + 1;
		int right_child = 2 * parent + 2;
		int largest_index = parent;//pret

		if (left_child < heap_size &&
			arr[left_child].priority > arr[largest_index].priority) {
			largest_index = left_child;
		}

		if (right_child < heap_size &&
			arr[right_child].priority > arr[largest_index].priority) {
			largest_index = right_child;
		}

		if (largest_index != parent) {
			swap_elements(arr, parent, largest_index);
			parent = largest_index;
		}
		else {
			break;
		}
	}
}

void sift_down_rec(Element* arr, int parent, int heap_size) {
	int left_child = 2 * parent + 1;
	int right_child = 2 * parent + 2;
	int largest_index = parent;

	if (left_child < heap_size &&
		arr[left_child].priority > arr[largest_index].priority) {
		largest_index = left_child;
	}

	if (right_child < heap_size &&
		arr[right_child].priority > arr[largest_index].priority) {
		largest_index = right_child;
	}

	if (largest_index != parent) {
		swap_elements(arr, parent, largest_index);
		sift_down_rec(arr, largest_index, heap_size);
	}
}

void create_priority_queue(PrioritetniRed *pq) {
	pq->size = 0;
}

void insert_element(PrioritetniRed *pq, int priority_value) {
	if (pq->size >= MAX_N) {
		// red je pun — ne ubacujemo
		return;
	}

	pq->array[pq->size].ignore = NULL; //na kraj, nemamo podata            
	pq->array[pq->size].priority = priority_value;

	sift_up_iter(pq->array, pq->size);

	pq->size++;
}

Element extract_max(PrioritetniRed *pq) {
	if (pq->size == 0) {
		Element empty = { NULL, -1 };//signal da nema niceg
		return empty;
	}

	Element max_element = pq->array[0];//naj el na vrhu
	pq->array[0] = pq->array[pq->size - 1];
	pq->size--;
	sift_down_iter(pq->array, 0, pq->size);

	return max_element;
}


void build_heap(Element* arr, int n) { //max-heap
	for (int i = n / 2 - 1; i >= 0; i--) {
		sift_down_iter(arr, i, n);
	}
}

void heap_sort(Element* arr, int n) {//uzl
	build_heap(arr, n);
	int heap_size = n;
	while (heap_size > 1) {
		swap_elements(arr, 0, heap_size - 1);//zam naj s zadnjim
		heap_size--;
		sift_down_iter(arr, 0, heap_size);
	}
}

void print_array(Element* arr, int n) {
	for (int i = 0; i < n; i++) {
		printf("%d ", arr[i].priority);
	}
	printf("\n");
}

int main() {
	PrioritetniRed my_pq;
	create_priority_queue(&my_pq);

	insert_element(&my_pq, 5);
	insert_element(&my_pq, 7);
	insert_element(&my_pq, 2);
	insert_element(&my_pq, 201);
	insert_element(&my_pq, 18);
	insert_element(&my_pq, 22);
	insert_element(&my_pq, 3010);

	printf("Prioritetni red nakon dodavanja (Gomila):\n");
	print_array(my_pq.array, my_pq.size);

	Element e = extract_max(&my_pq);
	printf("Izuzeti max: %d\n", e.priority);

	printf("Prioritetni red nakon uklanjanja Max:\n");
	print_array(my_pq.array, my_pq.size);

	// --- TEST HEAP SORTA ---
	Element sort_array[] = { {NULL, 10}, {NULL, 4}, {NULL, 15}, {NULL, 2}, {NULL, 20}, {NULL, 7} };
	int sort_n = sizeof(sort_array) / sizeof(sort_array[0]);

	printf("\nOriginalni niz za sortiranje:\n");
	print_array(sort_array, sort_n);

	heap_sort(sort_array, sort_n);

	printf("Niz nakon Heap Sorta (uzlazno):\n");
	print_array(sort_array, sort_n);

	return 0;
}
