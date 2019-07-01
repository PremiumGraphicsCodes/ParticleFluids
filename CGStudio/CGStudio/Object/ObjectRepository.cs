using PG.Core.Shape;
using PG.Core.UI;
using Reactive.Bindings;
using System.Collections.Generic;
using System.Collections.ObjectModel;
using System.Linq;

namespace PG.CGStudio
{
    public class ObjectRepository
    {
        public ReactiveCollection<ObjectModel> Objects { get; }

        public ObjectRepository()
        {
            this.Objects = new ReactiveCollection<ObjectModel>();
        }

        public void Clear()
        {
            Objects.Clear();
        }

        public void Sync()
        {
            this.Objects.Clear();
            /*
            var objects = adapter.GetObjects();
            foreach(var o in objects)
            {
                var item = new ObjectModel(o);
                this.Objects.Add(item);
            }

            this.PolygonMeshes.Sync();
            */
        }

        public ObjectModel FindObjectById(int id)
        {
            return Objects.FirstOrDefault(x => x.Id.Value == id);
        }
    }
}
