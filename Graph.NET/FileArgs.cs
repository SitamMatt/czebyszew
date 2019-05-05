using PowerArgs;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace Graph.NET
{
    class FileArgs
    {
        [ArgRequired(), ArgShortcut("-f"), ArgDescription("Path to file which contains the data"), ArgExistingFile]
        public string Function { get; set; }

        [ArgRequired(), ArgShortcut("-i"), ArgDescription("Path to file which contains the data"), ArgExistingFile]
        public string Interpolated { get; set; }

        [ArgRequired(), ArgShortcut("-n"), ArgDescription("Path to file which contains the data"), ArgExistingFile]
        public string Nodes { get; set; }
    }
}
