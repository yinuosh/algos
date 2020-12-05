using System;
using System.Collections;
using System.Collections.Concurrent;
using System.Collections.Generic;

namespace CSharp
{
    class Program
    {
        static void Main(string[] args)
        {
            Console.WriteLine("Hello World!");

            int arrLen = 10;
            int[] intArr = new int[arrLen]; ;
            Array.Fill<int>(intArr, 5);

            ArrayList arrList = new ArrayList(intArr);

            arrList.Add("a");
            arrList.Add(intArr);
            arrList.Add(int.MaxValue);

            List<int> list = new List<int>(intArr);
            list.Add(5);
            list.Remove(int.MaxValue);

            LinkedList<int> linkedList = new LinkedList<int>(list);
            var first = linkedList.First;
            var next = first.Next;

            Dictionary<int, string> dic = new Dictionary<int, string> { { 5, "5" },  { 6, "6" } };
            bool isSync;

            Hashtable ht = new Hashtable(dic);
            ht.Add("haha", 5);
            isSync = ht.IsSynchronized;
            var sycnedHt = Hashtable.Synchronized(ht);
            isSync = ht.IsSynchronized;

            ConcurrentBag<int> conBat = new ConcurrentBag<int> { 1, 2, 3, 3 };

            HashSet<int> hs = new HashSet<int>(intArr);
            SortedList sortedList1 = new SortedList();
            SortedList<int, string> sortedList = new SortedList<int, string>(dic);
            SortedSet<int> sortedSet = new SortedSet<int>(list);

            Stack stack = new Stack(sortedSet);
            var s1 = stack.Pop();
            var s2 = stack.Pop();
            stack.Push(intArr);

            Queue<int> q= new Queue<int>(intArr);
            var q1= q.Dequeue();

            BitArray bArr = new BitArray(intArr);
            bArr = bArr.Xor(bArr);
        }
    }
}
