using System;
using System.IO;
using System.Linq;
using System.Collections.Generic;
using System.Globalization;

namespace pz2
{
    class Program
    {
        static void Main(string[] args)
        {
            University university = new University();

            // Считываем из teachers.txt строки
            // и преобразует их в экземпляры класса Teacher
            // и запихивает их в университет
            foreach (var teacher in File.ReadAllLines("teachers.txt")
                    .Select(teacherString => Teacher.Parse(teacherString)))
                university.Add(teacher);

            // Считываем из students.txt строки
            // и преобразует их в экземпляры класса Student
            // и призывает их в университет
            foreach (var student in File.ReadAllLines("students.txt")
                    .Select(studentString => Student.Parse(studentString)))
                university.Add(student);

            Console.WriteLine("Добро пожаловать в наш интерфейс");
            Console.WriteLine("Введит <help> для просмотра команд");

            bool isQuit = false;
            string[] input;

            while (!isQuit)
            {
                Console.Write("> ");
                input = Console.ReadLine().Split();

                if (input.Length == 1 && input[0] == String.Empty)
                    continue;

                switch (input[0])
                {
                    case "help":
                        Console.WriteLine("add {student|teacher|person} [params] - добавить кого-нибудь");
                        Console.WriteLine("remove {student|teacher|person} [params] - удалить кого-нибудь");
                        Console.WriteLine("quit - выйти");
                        break;

                    case "add":
                        // TODO
                        // It's not working
                        if (input.Length > 1)
                            switch (input[1])
                            {
                                case "student":
                                    university.Add(Student.Parse());

                            }
                        else Console.WriteLine("add {student|teacher} [params] - добавить кого-нибудь");

                        break;

                    case "quit":
                        Console.WriteLine("Выходим...");
                        isQuit = true;
                        break;

                    default:
                        Console.WriteLine("Не понимаю, введите <help>");
                        break;
                }
            }

            // Считываем из teachers.txt строки
            // и преобразует их в экземпляры класса Teacher
            // и запихивает их в университет
            foreach (var teacher in File.ReadAllLines("teachers.txt")
                    .Select(teacherString => Teacher.Parse(teacherString)))
                university.Add(teacher);

            // Считываем из students.txt строки
            // и преобразует их в экземпляры класса Student
            // и призывает их в университет
            foreach (var student in File.ReadAllLines("students.txt")
                    .Select(studentString => Student.Parse(studentString)))
                university.Add(student);

            // Выводим по очереди сначала всех персон,
            // а затем студентов и учителей

            Console.WriteLine("\nВсе персоны:");
            foreach(var person in university.Persons)
                Console.WriteLine(person.ToString());

            Console.WriteLine("\nВсе студенты:");
            foreach(var student in university.Students)
                Console.WriteLine(student.ToString());

            Console.WriteLine("\nВсе учителя:");
            foreach(var teacher in university.Teachers)
                Console.WriteLine(teacher.ToString());

            //university.Remove(university.Teachers);
            //university.Remove((Student) university.Students);

            Console.WriteLine("\nИщем всех Пупкиных");
            foreach (var person in university.FindByLastName("Пупкин"))
                Console.WriteLine(person.ToString());

            // Пускаем волну отчислений
            Console.WriteLine("\nПускаем волну отчислений");

            foreach(var student in university.Students)
                university.Remove(student);


            Console.WriteLine("Студентов как не было:");
            foreach(var person in university.Persons)
                Console.WriteLine(person.ToString());
        }
    }


    static class Helper
    {
        public static int YearsFromSometimesToToday(DateTime someDate)
        {
            DateTime today = DateTime.Now;
            return today.Year - someDate.Year +
                ((someDate.Month >= today.Month && someDate.Day >= today.Day) ? -1 : 0);
        }
    }


    interface IPerson
    {
        string Name { get; }
        string Patronomic { get; }
        string LastName { get; }
        DateTime Date { get; }
        int Age { get; } 
    }


    class Student : IPerson
    {
        public Student(string name, string patronomic, string lastName,
                ushort course, string group, float averangeGrade, DateTime date)
        {
            Name = name;
            Patronomic = patronomic;
            LastName = lastName;
            Course = course;
            Group = group;
            AvarangeGrade = averangeGrade;
            Date = date;
        }

        public static Student Parse(string studentString)
        {
            var data = studentString.Split();
            Student student = new Student(
                    data[0], data[1], data[2], ushort.Parse(data[3]),
                    data[4], float.Parse(data[5]),
                    DateTime.ParseExact(data[6], @"dd/MM/yyyy", CultureInfo.InvariantCulture)
                    );

            return student;
        }

        public override string ToString()
        {
            string result = $"{Name} {Patronomic} {LastName}, {Course} c., {Group} gr., av. grade {AvarangeGrade}, birhday: {Date.ToString(@"dd/MM/yyyy")}";

            return result;
        }
        public string Name { get; }
        public string Patronomic { get; }
        public string LastName { get; }
        public DateTime Date { get; }
        public ushort Course { get; }
        public string Group { get; }
        public float AvarangeGrade { get; }
        public int Age
        {
            get => Helper.YearsFromSometimesToToday(Date); 
        }
    }



    class Teacher: IPerson
    {
        public enum Positions : ushort
        {
            None,
            Provost,
            Dean,
            DeputyDean,
            Teacher,
            GraduateStudent,
        }

        public Teacher(string name, string patronomic, string lastName,
                string department, Positions position,
                DateTime jobPlacement, DateTime date)
        {
            Name = name;
            LastName = lastName;
            Patronomic = patronomic;
            Department = department;
            Position = position;
            JobPlacement = jobPlacement;
            Date = date;
        }

        public static Teacher Parse(string teacherString)
        {
            var data = teacherString.Split();
            Teacher teacher = new Teacher(
                    data[0], data[1], data[2], data[3],
                    (Positions) Enum.Parse(typeof(Positions), data[4]),
                    DateTime.ParseExact(data[5], @"dd/MM/yyyy", CultureInfo.InvariantCulture),
                    DateTime.ParseExact(data[6], @"dd/MM/yyyy", CultureInfo.InvariantCulture)
                    );

            return teacher;
        }

        public override string ToString()
        {
            string result = $"{Name} {Patronomic} {LastName}, {Position}{Position == Positions.Provost ? "" : " of " + Department}, exp.: {Experience}, birhday: {Date.ToString(@"dd/MM/yyyy")}";

            return result;
        }
        public string Name { get; }
        public string Patronomic { get; }
        public string LastName { get; }
        public DateTime Date { get; }
        public string Department { get; }
        public Positions Position { get; }
        public DateTime JobPlacement { get; }
        public int Experience
        {
            get => Helper.YearsFromSometimesToToday(JobPlacement); 
        }
        public int Age
        {
            get => Helper.YearsFromSometimesToToday(Date); 
        }
    }


    interface IUniversity
    {
        void Add(IPerson person);
        void Remove(IPerson person);

        IEnumerable<IPerson> FindByLastName(string lastName);
        IEnumerable<Teacher> FindByDepartment(string text);

        IEnumerable<IPerson> Persons { get; } 
        IEnumerable<Student> Students { get; } 
        IEnumerable<Teacher> Teachers { get; } 
    }


    class University
    {
        private List<IPerson> persons = new List<IPerson>();

        public void Add(IPerson person)
        {
            persons.Add(person);
        }

        public void Remove(IPerson person)
        {
            persons.Remove(person);
        }

        public IEnumerable<IPerson> FindByLastName(string lastName)
        {
            return persons.Where(person => person.LastName == lastName)
                .OrderBy(person => person.LastName);
        }

        public IEnumerable<Teacher> FindByDepartment(string text)
        {
            return persons.OfType<Teacher>()
                .Where(teacher => teacher.Department == text)
                .OrderBy(teacher => teacher.Position);
        }


        public IEnumerable<IPerson> Persons
        {
            get => persons.OrderBy(person => person.Date);
        }

        public IEnumerable<Student> Students
        {
            get => persons.OfType<Student>().OrderBy(student => student.Date);
        }

        public IEnumerable<Teacher> Teachers
        {
            get => persons.OfType<Teacher>().OrderBy(teacher => teacher.Position);
        }
    }
}
