package com.itheima.springcloud.controller;
import org.springframework.web.bind.annotation.GetMapping;
import org.springframework.web.bind.annotation.PathVariable;
import org.springframework.web.bind.annotation.RestController;
import com.itheima.springcloud.po.Order;
import com.itheima.springcloud.util.ServiceInfoUtil;
@RestController
public class OrderController {
    /**
     * 通过id查询订单
     */
	@GetMapping("/order/{id}")
	public String findOrderById(@PathVariable String id) {
		System.out.println(ServiceInfoUtil.getPort());
		Order order = new Order();
		order.setId("123");
		order.setPrice(23.5);
		order.setReceiverAddress("北京市昌平区");
		order.setReceiverName("小韩");
		order.setReceiverPhone("13422343311");
		return order.toString();
	}
}