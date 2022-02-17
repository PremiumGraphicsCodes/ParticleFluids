using System.Collections;
using System.Collections.Generic;

namespace PG.Core
{
    public class CircularBuffer1d<T> : IEnumerable<T>
    {
        private readonly List<T> buffer;

        public int Count => this.buffer.Count;

        public CircularBuffer1d(int maxCapacity, T value)
        {
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

        public T this[int index]
        {
            get
            {
                return Get(index);
            }
            set
            {
                Set(index, value);
            }
        }

        public IEnumerator<T> GetEnumerator() => this.buffer.GetEnumerator();

        IEnumerator IEnumerable.GetEnumerator() => this.buffer.GetEnumerator();

        private int GetActualIndex(int index)
        {
            return index % Count;
        }
    }
}
