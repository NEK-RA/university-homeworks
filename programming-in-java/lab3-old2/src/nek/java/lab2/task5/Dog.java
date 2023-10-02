package nek.java.lab2.task5;

public class Dog {
    private String nickname;
    private double age;

    public Dog(String nickname, double age) {
        this.nickname = nickname;
        this.age = age;
    }

    public String getNickname() {
        return nickname;
    }

    public void setNickname(String nickname) {
        this.nickname = nickname;
    }

    public double getAge() {
        return age;
    }

    public double getHumanAge(){
        return age*7;
    }

    public void setAge(double age) {
        this.age = age;
    }

    @Override
    public String toString() {
        return "Собака {кличка='" + nickname + "', возраст=" + age + "}";
    }
}
