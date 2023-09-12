package nek.java.lab2.task4;

public class PC {
    private String cpu;
    private String gpu;
    private boolean externalGPU;
    private double price;

    PC(String cpu, String gpu, boolean externalGPU, double price) {
        this.cpu = cpu;
        this.gpu = gpu;
        this.externalGPU = externalGPU;
        this.price = price;
    }

    public String getCpu() {
        return cpu;
    }

    public void setCpu(String cpu) {
        this.cpu = cpu;
    }

    public String getGpu() {
        return gpu;
    }

    public void setGpu(String gpu) {
        this.gpu = gpu;
    }

    public boolean isExternalGPU() {
        return externalGPU;
    }

    public void setExternalGPU(boolean externalGPU) {
        this.externalGPU = externalGPU;
    }

    public double getPrice() {
        return price;
    }

    public void setPrice(double price) {
        this.price = price;
    }

    @Override
    public String toString() {
        return String.format("Характеристики ПК:\nМодель процессора: %s\nДискретная видеокарта: %b\nМодель " +
                "видеокарты: " + "%s\nЦена: %.5f", this.cpu, this.externalGPU, this.gpu, this.price);
    }
}
