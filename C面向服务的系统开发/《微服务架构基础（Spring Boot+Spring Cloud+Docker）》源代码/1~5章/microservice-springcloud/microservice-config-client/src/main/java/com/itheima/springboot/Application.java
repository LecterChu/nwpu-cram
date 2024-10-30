package com.itheima.springboot;
import org.springframework.beans.factory.annotation.Value;
import org.springframework.boot.SpringApplication;
import org.springframework.boot.autoconfigure.SpringBootApplication;
import org.springframework.cloud.context.config.annotation.RefreshScope;
import org.springframework.web.bind.annotation.RequestMapping;
import org.springframework.web.bind.annotation.RestController;
@SpringBootApplication
@RefreshScope
@RestController
public class Application {
	@Value("${clientParam}")
	private String clientParam;
	
	@RequestMapping("/clientParam")
	public String getParam(){
		return this.clientParam;
	}
	
	@RequestMapping("/hello")
    public String hello(){
    	return "hello world";
    }
	public static void main(String[] args) {
		SpringApplication.run(Application.class, args);
	}
}