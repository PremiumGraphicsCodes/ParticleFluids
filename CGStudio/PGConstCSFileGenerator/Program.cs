using System.Collections.Generic;
using System.IO;

namespace PGConstCSFileGenerator
{
    class PublicConstant
    {
        public string Key { get; }
        public string Value { get; }
        public string ToCSSource()
        {
            return "public const string " + Key + " = " + Value;
        }
    }

    class PublicConstants
    {
        public string Name { get; private set; }

        public List<PublicConstant> Constants { get; private set; }
            = new List<PublicConstant>();

        public void ParseCPPFile(string filePath)
        {
            this.Name = Path.GetFileNameWithoutExtension(filePath);

        }

        public string ToCSSource(string filePath)
        {
            return "";
        }
    }

    class CPPLine
    {
        CPPLine()
        {

        }
    }

    class Program
    {
        static void Main(string[] args)
        {
        }
    }
}
