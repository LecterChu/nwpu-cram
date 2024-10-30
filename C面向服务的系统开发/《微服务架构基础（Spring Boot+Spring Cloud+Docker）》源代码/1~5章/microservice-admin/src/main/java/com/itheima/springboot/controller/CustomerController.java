package com.itheima.springboot.controller;
import org.springframework.jms.annotation.JmsListener;
import org.springframework.web.bind.annotation.RestController;
/**
 * 客户控制器
 */
@RestController
public class CustomerController {
	/**
	 * 监听和读取消息
	 */
	@JmsListener(destination = "active.queue")
	public void readActiveQueue(String message) {
		System.out.println("接收到："+message);
	}
}