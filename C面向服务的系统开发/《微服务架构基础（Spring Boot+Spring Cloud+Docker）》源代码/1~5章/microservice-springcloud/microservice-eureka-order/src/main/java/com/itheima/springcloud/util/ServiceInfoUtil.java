package com.itheima.springcloud.util;
import org.springframework.boot.context.embedded.EmbeddedServletContainerInitializedEvent;
import org.springframework.context.ApplicationListener;
import org.springframework.context.annotation.Configuration;
/**
 * 服务信息工具类（监听服务实例端口）
 */
@Configuration // 注册组件
public class ServiceInfoUtil implements 
             ApplicationListener<EmbeddedServletContainerInitializedEvent> {
	/**
	 * 声明event对象，该对象用于获取运行服务器的本地端口
	 */
	private static EmbeddedServletContainerInitializedEvent event;
	@Override
	public void onApplicationEvent(
			EmbeddedServletContainerInitializedEvent event) {
		ServiceInfoUtil.event = event;
	}
	/**
	 * 获取端口号
	 */
	public static int getPort() {
		int port = event.getEmbeddedServletContainer().getPort();
		return port;
	}
}