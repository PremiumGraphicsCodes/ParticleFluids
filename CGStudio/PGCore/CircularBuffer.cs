﻿using System.Collections;
using System.Collections.Generic;

namespace PG.Core
{
    public class CircularBuffer<T> : IEnumerable<T>
    {
        private List<T> buffer;

        public int Count => this.buffer.Count;

        public int MaxCapacity { get; private set; }

        public CircularBuffer(int maxCapacity, T value)
        {
            this.MaxCapacity = maxCapacity;
            this.buffer = new List<T>();
            for(int i = 0; i < maxCapacity; ++i)
            {
                this.buffer.Add(value);
            }
        }

        public T Get(int index)
        {
            var ai = GetActualIndex(index);
            return buffer[ai];
        }

        public void Set(int index, T value)
        {
            var ai = GetActualIndex(index);
            buffer[ai] = value;
        }

        public IEnumerator<T> GetEnumerator() => this.buffer.GetEnumerator();

        IEnumerator IEnumerable.GetEnumerator() => this.buffer.GetEnumerator();

        private int GetActualIndex(int index)
        {
            return index % MaxCapacity;
        }
    }
}
