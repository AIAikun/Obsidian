# Go 语言方法(Method)

Go语言支持方法。Go方法与Go函数相似，但有一点不同，就是方法中包含一个接收者参数。在接收者参数的帮助下，该方法可以访问接收者的属性。在这里，接收方可以是结构类型或非结构类型。在代码中创建方法时，接收者和接收者类型必须出现在同一个包中。而且不允许创建一个方法，其中的接收者类型已经在另一个包中定义，包括像int、string等内建类型。如果您尝试这样做，那么编译器将抛出错误。

**语法：**
``` go
func(reciver_name Type) method_name(parameter_list)(return_type){
    // Code
}
```


在此，可以在方法内访问接收器。

## 结构类型接收器的方法

在Go语言中，允许您定义其接收者为结构类型的方法。可以在方法内部访问此接收器，如以下示例所示：
``` go
package main 
  
import "fmt"
  
//Author 结构体
type author struct { 
    name      string 
    branch    string 
    particles int
    salary    int
} 
  
//接收者的方法 
func (a author) show() { 
  
    fmt.Println("Author's Name: ", a.name) 
    fmt.Println("Branch Name: ", a.branch) 
    fmt.Println("Published articles: ", a.particles) 
    fmt.Println("Salary: ", a.salary) 
} 
  
func main() { 
  
    //初始化值
    //Author结构体
    res := author{ 
        name:      "Sona", 
        branch:    "CSE", 
        particles: 203, 
        salary:    34000, 
    } 
  
    //调用方法
    res.show() 
}
```

**输出：**
```
Author's Name:  Sona
Branch Name:  CSE
Published articles:  203
Salary:  34000

```

## 非结构类型接收器的方法

在Go语言中，只要类型和方法定义存在于同一包中，就可以使用非结构类型接收器创建方法。如果它们存在于int，string等不同的包中，则编译器将抛出错误，因为它们是在不同的包中定义的。
``` go 
package main 
  
import "fmt"
  
//类型定义
type data int

//定义一个方法
//非结构类型的接收器 
func (d1 data) multiply(d2 data) data { 
    return d1 * d2 
} 
  
/* 
//如果您尝试运行此代码，

//然后编译器将抛出错误 
func(d1 int)multiply(d2 int)int{ 
return d1 * d2 
} 
*/
  
func main() { 
    value1 := data(23) 
    value2 := data(20) 
    res := value1.multiply(value2) 
    fmt.Println("最终结果: ", res) 
}

```


最终结果:  460

## 带指针接收器的Go方法

在Go语言中，允许您使用**指针**接收器创建方法。在指针接收器的帮助下，如果方法中所做的更改将反映在调用方中，这对于值接收器是不可能的。

**语法：**
``` go
func (p *Type) method_name(...Type) Type {
    // Code
}

```

``` go
package main 
  
import "fmt"
  
// Author 结构体
type author struct { 
    name      string 
    branch    string 
    particles int
} 
  
//方法，使用author类型的接收者
func (a *author) show(abranch string) { 
    (*a).branch = abranch 
} 
  
// Main function 
func main() { 
  
    //初始化author结构体
    res := author{ 
        name:   "Sona", 
        branch: "CSE", 
    } 
  
    fmt.Println("Author's name: ", res.name) 
    fmt.Println("Branch Name(Before): ", res.branch) 
  
    //创建一个指针
    p := &res 
  
    //调用show方法
    p.show("ECE") 
    fmt.Println("Author's name: ", res.name) 
    fmt.Println("Branch Name(After): ", res.branch) 
}
```

**输出：**
```
Author's name:  Sona
Branch Name(Before):  CSE
Author's name:  Sona
Branch Name(After):  ECE

```

## 方法可以接受指针和值

众所周知，在Go中，当一个函数具有值参数时，它将仅接受参数的值，如果您尝试将指针传递给值函数，则它将不接受，反之亦然。但是Go方法可以接受值和指针，无论它是使用指针还是值接收器定义的。如下例所示：

``` go
package main 
  
import "fmt"
  
// Author 结构体
type author struct { 
    name   string 
    branch string 
} 
  
//带有指针的方法
//author类型的接收者
func (a *author) show_1(abranch string) { 
    (*a).branch = abranch 
} 
  
//带有值的方法
//作者类型的接收者 
func (a author) show_2() { 
    a.name = "Gourav"
    fmt.Println("Author's name(Before) : ", a.name) 
} 
  

func main() { 
  
     //初始化值
     //作者结构体
    res := author{ 
        name:   "Sona", 
        branch: "CSE", 
    } 
  
    fmt.Println("Branch Name(Before): ", res.branch) 
  
     //调用show_1方法
     //（指针方法）带有值
    res.show_1("ECE") 
    fmt.Println("Branch Name(After): ", res.branch) 
  
     //调用show_2方法
     //带有指针的（值方法）
    (&res).show_2() 
    fmt.Println("Author's name(After): ", res.name) 
}

```


**输出：**
``` 
Branch Name(Before):  CSE
Branch Name(After):  ECE
Author's name(Before) :  Gourav
Author's name(After):  Sona

```

## 方法和函数之间的差异

|方法|函数|
|---|---|
|它包含接收器。|它不包含接收器。|
|它可以接受指针和值。|它不能同时接受指针和值。|
|可以在程序中定义相同名称但不同类型的方法。|程序中不允许定义相同名称但不同类型的函数。|