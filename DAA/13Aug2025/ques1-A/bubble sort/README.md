# Bubble Sort Algorithm in C

## 📌 Overview
This project demonstrates the **Bubble Sort** algorithm implemented in C.  
Bubble Sort is a simple comparison-based sorting technique where the largest element "bubbles" to the end in each pass. The process is repeated until the array is fully sorted.  

---

## ⚡ Algorithm

**Steps:**
1. Start from the first element of the array.  
2. Compare the current element with the next element.  
3. If the current element is greater than the next, swap them.  
4. Repeat steps 2–3 for all elements, reducing the range by one each time.  
5. Continue the process for `n-1` passes or until no swaps are needed.  

###Pseudocode
'''
procedure BubbleSort(A[1..n]) 

    for i ← 1 to n-1 do
        swapped ← false
        for j ← 1 to n-i do
            if A[j] > A[j+1] then
                swap A[j] and A[j+1]
                swapped ← true
            end if
        end for
        if swapped = false then
            break   // No swaps means array is sorted
        end if
    end for
end procedure