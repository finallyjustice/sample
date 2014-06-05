
public class Main {
	public static void main(String[] args) {
		Storage storage = new Storage();
		Thread consumer = new Thread(new Consumer(storage));
		Thread producer = new Thread(new Producer(storage));
		
		consumer.setName("Consumer");
		producer.setName("Producer");
		
		consumer.start();
		producer.start();
	}
}
