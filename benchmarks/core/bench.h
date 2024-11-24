/**
 * Benchmarking utilities for Quickfall.
 */

char** categories;

long* timeTaken;

/**
 * Sets the active benchmarking categories.
 * @param count the count of categories in the array.
 * @param the category array.
 */
void setCategories(int count, char* categories[]) {};

/**
 * Stops the current benchmarking timer.
 * @param category the initiator category of this.
 */
void stopBenchmarkTimer(int category);

/**
 * Starts a benchmarking timer.
 */
void startBenchmarkTimer();
