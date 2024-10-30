package com.example.group6.controller;

import org.springframework.stereotype.Controller;
import org.springframework.web.bind.annotation.RequestMapping;
import org.springframework.web.bind.annotation.ResponseBody;



@ResponseBody
@Controller
public class OrderController {
    @RequestMapping("order")
    public String order(){
        return "Hello Order";
    }
}