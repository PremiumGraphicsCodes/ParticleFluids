namespace PG.Core
{
    public class ObjectId
    {
        public int parentId;
        public int childId;

        public ObjectId()
        { }

        public ObjectId(int parentId, int childId)
        {
            this.parentId = parentId;
            this.childId = childId;
        }
    }
}
