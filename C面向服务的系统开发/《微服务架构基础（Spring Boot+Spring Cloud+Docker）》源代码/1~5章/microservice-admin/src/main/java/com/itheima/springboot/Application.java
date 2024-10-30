package com.itheima.springboot;
import javax.jms.Queue;
import org.apache.activemq.command.ActiveMQQueue;
import org.springframework.boot.SpringApplication;
import org.springframework.boot.autoconfigure.SpringBootApplication;
import org.springframework.cache.annotation.EnableCaching;
import org.springframework.context.annotation.Bean;
@SpringBootApplication
@EnableCaching  //开启缓存
public class Application {
	/**
	 * 创建消息队列对象
	 */
	@Bean
    public Queue queue() {
       return new ActiveMQQueue("active.queue");
    }
	/**
	 * 启动方法
	 */
	public static void main(String[] args) {
		SpringApplication.run(Application.class, args);
	}
}