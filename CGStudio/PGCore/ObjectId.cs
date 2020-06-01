namespace PG.Core
{
    public class SceneId
    {
        public int parentId;
        public int childId;

        public SceneId()
        { }

        public SceneId(int parentId, int childId)
        {
            this.parentId = parentId;
            this.childId = childId;
        }
    }
}
