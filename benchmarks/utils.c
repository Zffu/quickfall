/**
 * Utilities to use while Benchmarking Quickfall.
 */

#include <windows.h>
#include <stdio.h>


//
//
// Timing Utilities
//
//

LARGE_INTEGER frequency, start, end;

int categoriesSize;
char** categories;

/**
 * Sets the categories for the Quickfall Benchmarking Context.
 */
void setCategories(int amount, char* categories[]) {
    categories = categories;
    categoriesSize = amount;
}

/**
 * Starts the monitoring
 */
void startMonitoring() {
    QueryPerformanceFrequency(&frequency);
    QueryPerformanceCounter(&start);
}

/**
 * Stops monitoring the current benchmark context.
 */
void stopMonitoring(int category) {
    QueryPerformanceCounter(&end);
    float taken = (end.QuadPart - start.QuadPart) * 1000000000.0 / frequency.QuadPart;
}
