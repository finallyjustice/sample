
public class Consumer implements Runnable{
	private Storage storage;
	
	public Consumer(Storage storage) {
		this.storage = storage;
	}
	
	public void run() {
		for(int i=0; i<100; i++) {
			storage.pop();
			try {
				Thread.sleep(20000);
			} catch (InterruptedException e) {
				e.printStackTrace();
			}
		}
	}
}
