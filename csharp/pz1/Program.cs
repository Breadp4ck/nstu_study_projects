using System;
using System.Collections.Generic;
using System.IO;
using System.Linq;

namespace pz1_sharp
{
    class Program
    {
        static void Main(string[] args)
        {
            Console.Write("Инвёрс или нет? (да, нет) > ");
            bool isReverse = false; bool isAnswered = false;

            while (!isAnswered)
                switch (Console.ReadLine())
                {
                    case "да":
                        isReverse = true;
                        isAnswered = true;
                        break;

                    case "нет":
                        isAnswered = true;
                        break;

                    default:
                        Console.Write("Не понел? (да, нет) > ");
                        break;
                }

            Person[] persons = File.ReadAllLines("persons.txt").
                Select(person_string => Person.Parse(person_string)).ToArray();

            string[] person_strings = persons.OrderBy(person => person.Surname)
                .Select(person => person.ToString()).ToArray();
            if (isReverse) Array.Reverse(person_strings);

            File.WriteAllLines("out.txt", person_strings);
        }
    }

    class Person
    {
        private bool sex;

        public Person(string surname, string first_name, string second_name,
                bool sex, float weight, DateTime birth_date)
        {
            Surname = surname;
            FirstName = first_name;
            SecondName = second_name;
            this.sex = sex;
            Height = weight;
            BirthDate = birth_date;
        }

        public static Person Parse(string person_string)
        {
            var data = person_string.Split();
            Person person = new Person(
                    data[0], data[1], data[2],
                    data[3] == "Male" ? true : false,
                    float.Parse(data[4]),
                    DateTime.Parse(data[5])
                    );

            return person;
        }

        public override string ToString()
        {
            string result = $"{Surname} {FirstName} {SecondName}, {sex ? "Male" : "Female"}, {Height:F4}m, {BirthDate.ToString(@"dd\/MM\/yyyy")} ({YearsOld})";

            return result;
        }

        public string Surname { private set; get; }
        public string FirstName { private set; get; }
        public string SecondName { private set; get; }
        public bool Sex { get { return sex; } }
        public float Height { private set; get; }
        public DateTime BirthDate { private set; get; }
        public int YearsOld 
        {
            get
            {
                DateTime today = DateTime.Now;
                return DateTime.Now.Year - BirthDate.Year +
                    ((BirthDate.Month >= today.Month && BirthDate.Day >= today.Day) ? -1 : 0);
            }
        }
    }
}
