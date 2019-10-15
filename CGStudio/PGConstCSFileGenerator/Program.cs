using System.Collections.Generic;
using System.IO;
using System.Linq;

namespace PGConstCSFileGenerator
{
    class CPPLine
    {
        private string[] tokens;

        public CPPLine(string line)
        {
            tokens = line.Split(' ');
        }

        public bool IsPublicLine()
        {
            if (tokens.Count() < 4)
            {
                return false;
            }
            return (tokens[0].Trim('\t') == "PublicLabel");
        }

        public PublicLabel ToPublicLabel()
        {
            var key = tokens[1].Trim('\t');
            var value = tokens[3].Trim(';');
            return new PublicLabel(key, value);
        }
    }

    class PublicLabel
    {
        public string Key { get; }

        public string Value { get; }

        public PublicLabel(string key, string value)
        {
            this.Key = key;
            this.Value = value;
        }

        public string ToCSSource()
        {
            return "public const string " + Key + " = " + Value + ";";
        }
    }

    class PublicLabelBlock
    {
        public string Name { get; private set; }

        public List<PublicLabel> Constants { get; private set; }
            = new List<PublicLabel>();

        public void ParseCPPFile(string filePath)
        {
            this.Name = Path.GetFileNameWithoutExtension(filePath);
            using (var reader = new StreamReader(filePath))
            {
                while(!reader.EndOfStream)
                {
                    var line = reader.ReadLine();
                    var cppLine = new CPPLine(line);
                    if(cppLine.IsPublicLine())
                    {
                        this.Constants.Add(cppLine.ToPublicLabel());
                    }
                }
            }
        }

        public string ToCSSource()
        {
            var writer = new StringWriter();
            writer.WriteLine("\tpublic class " + Name);
            writer.WriteLine("\t{");
            foreach (var c in Constants)
            {
                writer.WriteLine("\t\t" + c.ToCSSource());
            }
            writer.WriteLine("\t}");
            return writer.ToString();
        }
    }

    class Program
    {
        static void Main(string[] args)
        {
            var cppDirectory = args[0];
            var cppFiles = Directory.EnumerateFiles(cppDirectory);
            var blocks = new List<PublicLabelBlock>();
            foreach (var file in cppFiles)
            {
                var block = new PublicLabelBlock();
                block.ParseCPPFile(file);
                blocks.Add(block);
            }

            var csFile = args[1];
            using (var writer = new StreamWriter(csFile))
            {
                writer.WriteLine("namespace PG {");
                foreach (var block in blocks)
                {
                    writer.WriteLine(block.ToCSSource());
                }
                writer.WriteLine("}");
            }
        }
    }
}
