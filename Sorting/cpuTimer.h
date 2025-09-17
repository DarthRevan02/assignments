/*
 * Author : Pravin Chandra
 * Date   : 03-09-2025
 * File   : cpuTimer.h
 * Desc   : A header file that declares a function for measuring CPU time
 *          across platforms (Windows, Linux, macOS).
 * Remarks: Checked for Win32, Win64, Linux, and macOS.
 */

#ifndef CPUTIMER_H_
#define CPUTIMER_H_

// Conditional includes based on the operating system
#ifdef _WIN32
#include <windows.h>
#elif __APPLE__ && __MACH__
#include <mach/mach_time.h>
#elif __linux__
#include <sys/time.h>
#include <sys/resource.h>
#endif

// Function to get the current CPU time in seconds
double getCpuTime();

#endif // CPUTIMER_H_
