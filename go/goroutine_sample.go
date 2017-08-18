package main

import (
	"fmt"
)

func sum(arr []int, c chan int) {
	num := 0
	for _, v := range arr {
		num += v
	}

	c <- num
}

func main() {
	c := make(chan int)
	slice := []int{1, 2, 3, 4, 5, 6, 7, 8, 9, 10}

	go sum(slice[0:len(slice)/2], c)
	go sum(slice[len(slice)/2:], c)
	num1, num2 := <-c, <-c

	fmt.Println(num1, num2, num1+num2)
}
