class Employee {
    String name;
    double salary;
    int age;
}

class Teacher extends Employee {
    int id;
    String rank;

    Teacher(int id, String name, double salary) {
        this.id = id;
        this.name = name;
        this.salary = salary;
    }
}

class Officer extends Employee {
    int id;
    String rank;

}

class payroll_system {
    public static void main(String[] args) {
        // System.out.println("hello");
        Teacher t = new Teacher(20, "Rayhan", 250000);
        System.out.println("Teacher = " + t.name);
        System.out.println("Teacher id = " + t.id);
        System.out.println("Teacher salary= " + t.salary);
        Officer mamun = new Officer();
        mamun.name = "Mamun";
        mamun.rank = "Supervisor";
        mamun.salary = 2000;
        mamun.age = 29;
        System.out.println("Officer = " + mamun.name);
        System.out.println("Officer id = " + mamun.id);
        System.out.println("Officer salary= " + mamun.salary);
    }
}