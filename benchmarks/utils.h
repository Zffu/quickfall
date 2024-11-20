/**
 * Utilities to use while Benchmarking Quickfall.
 */

#ifndef BENCHMARK_UTILS_H
#define BENCHMARK_UTILS_H

//
//
// Timing Utilities
//
//

/**
 * Sets the categories for the Quickfall Benchmarking Context.
 */
void setCategories(int amount, char* categories[]);

/**
 * Starts the monitoring
 */
void startMonitoring();

/**
 * Stops monitoring the current benchmark context.
 */
void stopMonitoring(int category);

#endif