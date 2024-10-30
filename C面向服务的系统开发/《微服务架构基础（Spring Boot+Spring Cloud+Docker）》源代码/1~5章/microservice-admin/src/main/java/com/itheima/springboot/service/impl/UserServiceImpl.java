package com.itheima.springboot.service.impl;
import java.util.List;
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.cache.annotation.CacheEvict;
import org.springframework.cache.annotation.Cacheable;
import org.springframework.stereotype.Service;
import org.springframework.transaction.annotation.Transactional;
import com.itheima.springboot.mapper.UserMapper;
import com.itheima.springboot.po.User;
import com.itheima.springboot.service.UserService;
@Service
@Transactional
public class UserServiceImpl implements UserService{
	// 注入用户Mapper
	@Autowired
	private UserMapper userMapper;
	// 查询所有用户
	@Cacheable(value="UserCache",key="'user.getAllUsers'")
	public List<User> getAllUsers() {
		return this.userMapper.getAllUsers();
	}
	// 删除用户
	@CacheEvict(value="UserCache",key="'user.getAllUsers'")
	public void deleteUser(Integer id) {
		this.userMapper.delete(id);
		System.out.println("删除了id为"+id+"的用户");
	}
}