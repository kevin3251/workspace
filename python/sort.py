#!/usr/bin/env python3
# -*- coding: utf-8 -*-
def  insertion_sort(s):
    if not s:
        return []
    d = [s.pop()]
    s_len = len(s)
    d_len = len(d)
    for i in range ( s_len):
        temp = s.pop()
        for j in range(d_len):
            if  d[j] >= temp:
                d.insert(j,temp)
                d_len += 1
                break
            if j == (d_len-1):
                d.append(temp)
    return d

def selection_sort(s):
    s_len= len(s)
    d =list()
    for i in range(s_len, 0, -1):
        temp = s.pop(s.index(max(s[:i])))
        d.insert(0,temp)
    return d


def heap_sort(s):
    def swap(s,a,b):
         s[a], s[b] = s[b], s[a]
        
    def heapify(s, idx, length):
        left = 2 * idx + 1
        right = 2 * idx +2
        if  (left  < length) and  (s[left]  >  s [idx]):
            largest = left
        else:
            largest = idx
            
        if (right < length) and (s[right] > s[largest]):
            largest = right 
        if largest != idx:
            swap(s,idx,largest)
            heapify (s, largest, length)
    
    length = len(s) -1
    idx =int(length /2)
    for i in range(idx, -1, -1):
        heapify(s, i, length)

    for i in range(length, 0, -1):
            swap(s,0,i)
            heapify(s, 0, i)
    return s


def quick_sort(s):
    if len(s) <= 1:
        return s
    left = [ i for i in s[1:] if i <= s[0]]
    right =  [ i for i in s[1:] if i > s[0]]
    return quick_sort(left) + [s[0]] + quick_sort(right)
            

def bucket_sort(s):
    n = len(s)
    buckets = [list() for i in range(n)] 

    for i in range(n):
        buckets[int(s[i]/n)].append(s[i])

    d = list()
    for i in range(n):
        sorted_bucket = insertion_sort(buckets[i])
        d.extend(sorted_bucket)

    return d
