using System.Collections;
using System.Collections.Generic;

namespace PG.Core
{
    public class CircularBuffer2d<T> : IEnumerable<CircularBuffer1d<T>>
    {
        private readonly List<CircularBuffer1d<T>> buffer;

        public int Count => this.buffer.Count;

        public CircularBuffer2d(int uCount, int vCount, T value)
        {
            this.buffer = new List<CircularBuffer1d<T>>();
            for (int i = 0; i < uCount; ++i)
            {
                this.buffer.Add(new CircularBuffer1d<T>( vCount, value) );
            }
        }

        public CircularBuffer1d<T> Get(int index)
        {
            var ai = GetActualIndex(index);
            return buffer[ai];
        }

        public void Set(int index, CircularBuffer1d<T> value)
        {
            var ai = GetActualIndex(index);
            buffer[ai] = value;
        }

        public CircularBuffer1d<T> this[int index]
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

        private int GetActualIndex(int index)
        {
            return index % Count;
        }

        public IEnumerator<CircularBuffer1d<T>> GetEnumerator()
        {
            return buffer.GetEnumerator();
        }

        IEnumerator IEnumerable.GetEnumerator()
        {
            return buffer.GetEnumerator();
        }
    }
}
