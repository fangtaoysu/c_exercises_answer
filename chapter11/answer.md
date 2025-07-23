# 简答题

## 11.1

预处理在在编译时展开，而函数是在运行时调用，因此预处理效率更高。
然而预处理的可读性更差，且无参数验证，调试起来也更复杂，因此仅适用于简单小型的操作。

## 11.2

### 样例
```h
// mylib_portable.h
/**
 * 跨平台兼容性宏定义
 * 功能：自动识别平台/编译器/架构，提供统一接口
 * 版本：1.2.0
 */

#ifndef MYLIB_PORTABLE_H
#define MYLIB_PORTABLE_H

// ==================== 编译器特性检测 ====================
#if defined(__GNUC__) && !defined(__clang__)
    #define MYLIB_COMPILER_GCC      1
    #define MYLIB_GCC_VERSION       (__GNUC__ * 100 + __GNUC_MINOR__)
#elif defined(__clang__)
    #define MYLIB_COMPILER_CLANG    1
    #define MYLIB_CLANG_VERSION     (__clang_major__ * 100 + __clang_minor__)
#elif defined(_MSC_VER)
    #define MYLIB_COMPILER_MSVC     1
    #define MYLIB_MSVC_VERSION      _MSC_VER
#else
    #warning "Unknown compiler"
#endif

// ==================== 操作系统检测 ====================
#if defined(_WIN32) || defined(_WIN64)
    #define MYLIB_OS_WINDOWS        1
    #ifdef _WIN64
        #define MYLIB_OS_WIN64      1
    #else
        #define MYLIB_OS_WIN32      1
    #endif
#elif defined(__linux__)
    #define MYLIB_OS_LINUX          1
#elif defined(__APPLE__) && defined(__MACH__)
    #include <TargetConditionals.h>
    #if TARGET_OS_MAC
        #define MYLIB_OS_MACOS      1
    #elif TARGET_OS_IPHONE
        #define MYLIB_OS_IOS        1
    #endif
#elif defined(__ANDROID__)
    #define MYLIB_OS_ANDROID        1
#else
    #error "Unsupported operating system"
#endif

// ==================== CPU架构检测 ====================
#if defined(__x86_64__) || defined(_M_X64)
    #define MYLIB_ARCH_X64          1
#elif defined(__i386__) || defined(_M_IX86)
    #define MYLIB_ARCH_X86          1
#elif defined(__arm__) || defined(__aarch64__)
    #define MYLIB_ARCH_ARM          1
    #if defined(__aarch64__)
        #define MYLIB_ARCH_ARM64    1
    #endif
#endif

// ==================== 特性控制宏 ====================
// 动态库导入导出
#if defined(MYLIB_OS_WINDOWS)
    #ifdef MYLIB_DLL_EXPORTS
        #define MYLIB_API __declspec(dllexport)
    #else
        #define MYLIB_API __declspec(dllimport)
    #endif
    #define MYLIB_CALL __stdcall
#else
    #define MYLIB_API __attribute__((visibility("default")))
    #define MYLIB_CALL
#endif

// 字节序检测
#if (defined(__BYTE_ORDER__) && (__BYTE_ORDER__ == __ORDER_LITTLE_ENDIAN__)) || \
    defined(MYLIB_OS_WINDOWS)
    #define MYLIB_LITTLE_ENDIAN     1
#elif defined(__BYTE_ORDER__) && (__BYTE_ORDER__ == __ORDER_BIG_ENDIAN__)
    #define MYLIB_BIG_ENDIAN        1
#else
    #error "Cannot determine endianness"
#endif

// ==================== 实用宏 ====================
// 安全释放宏
#define MYLIB_SAFE_FREE(p) do { if(p) { free(p); (p) = NULL; } } while(0)

// 跨平台路径分隔符
#if defined(MYLIB_OS_WINDOWS)
    #define MYLIB_PATH_SEP '\\'
#else
    #define MYLIB_PATH_SEP '/'
#endif

// 禁用拷贝构造
#define MYLIB_DISABLE_COPY(ClassName) \
    ClassName(const ClassName&) = delete; \
    ClassName& operator=(const ClassName&) = delete

// ==================== 调试支持 ====================
#ifdef MYLIB_DEBUG
    #define MYLIB_ASSERT(expr) \
        do { \
            if (!(expr)) { \
                fprintf(stderr, "[ASSERT] %s:%d (%s)\n", \
                       __FILE__, __LINE__, #expr); \
                abort(); \
            } \
        } while(0)
    
    #define MYLIB_LOG(fmt, ...) \
        fprintf(stderr, "[LOG] %s:%d: " fmt "\n", \
                __FILE__, __LINE__, ##__VA_ARGS__)
#else
    #define MYLIB_ASSERT(expr) ((void)0)
    #define MYLIB_LOG(fmt, ...) ((void)0)
#endif

// ==================== C++特性封装 ====================
#ifdef __cplusplus
    // C++11特性检测
    #if __cplusplus >= 201103L
        #define MYLIB_CPP11         1
        #define MYLIB_NOEXCEPT      noexcept
    #else
        #define MYLIB_NOEXCEPT      throw()
    #endif
    
    // 移动语义支持
    #if __cplusplus >= 201103L
        #define MYLIB_MOVE(x)       std::move(x)
    #else
        #define MYLIB_MOVE(x)       (x)
    #endif
#endif

#endif // MYLIB_PORTABLE_H
```
### 样例功能
#### **1. 环境检测功能**

| 类别             | 宏定义示例            | 功能描述                             |
| ---------------- | --------------------- | ------------------------------------ |
| **编译器检测**   | `MYLIB_COMPILER_GCC`  | 识别GCC/Clang/MSVC等编译器类型和版本 |
| **操作系统检测** | `MYLIB_OS_WINDOWS`    | 检测Windows/Linux/macOS/iOS/Android  |
| **CPU架构检测**  | `MYLIB_ARCH_X64`      | 识别x86/x64/ARM/ARM64等CPU架构       |
| **字节序检测**   | `MYLIB_LITTLE_ENDIAN` | 判断系统是否为小端模式               |

---

#### **2. 跨平台兼容功能**

| 类别             | 宏定义示例        | 功能描述                                              |
| ---------------- | ----------------- | ----------------------------------------------------- |
| **动态库导出**   | `MYLIB_API`       | 自动适配Windows的`__declspec`和Unix的`visibility`属性 |
| **调用约定**     | `MYLIB_CALL`      | 标准化函数调用约定（Windows下默认为`__stdcall`）      |
| **路径分隔符**   | `MYLIB_PATH_SEP`  | 自动选择`/`或`\`作为路径分隔符                        |
| **安全内存管理** | `MYLIB_SAFE_FREE` | 带NULL检查的内存释放宏                                |

---

#### **3. 开发辅助功能**

| 类别         | 宏定义示例           | 功能描述                               |
| ------------ | -------------------- | -------------------------------------- |
| **调试断言** | `MYLIB_ASSERT`       | 带文件名/行号信息的调试断言            |
| **日志输出** | `MYLIB_LOG`          | 格式化日志输出（自动附加文件行号信息） |
| **禁用拷贝** | `MYLIB_DISABLE_COPY` | 快速生成删除拷贝构造/赋值的代码        |

---

#### **4. C++特性支持**

| 类别             | 宏定义示例       | 功能描述                                 |
| ---------------- | ---------------- | ---------------------------------------- |
| **异常规范**     | `MYLIB_NOEXCEPT` | 自动适配C++11的`noexcept`或旧式`throw()` |
| **移动语义**     | `MYLIB_MOVE`     | 条件启用C++11的`std::move`支持           |
| **标准版本检测** | `MYLIB_CPP11`    | 检测C++11及以上特性可用性                |

---

#### **5. 防御性编程设计**

| 特性             | 实现方式                      | 作用说明                         |
| ---------------- | ----------------------------- | -------------------------------- |
| **错误提前终止** | `#error "Unsupported OS"`     | 遇到不支持的平台立即报错终止编译 |
| **多重括号保护** | `#define MULT(a,b) ((a)*(b))` | 防止宏展开时的运算符优先级问题   |
| **作用域隔离**   | `#undef TEMP_MACRO`           | 避免宏污染其他代码区域           |

---

#### **典型使用场景示例**

1. **跨平台动态库开发**

   ```c
   MYLIB_API void MYLIB_CALL InitLibrary();  // 自动适配不同平台的导出规则
   ```

2. **安全内存操作**

   ```c
   char* buffer = malloc(1024);
   MYLIB_SAFE_FREE(buffer);  // 安全释放且置NULL
   ```

3. **平台特定代码**

   ```c
   #if defined(MYLIB_OS_WINDOWS)
       WindowsSpecificFunction();
   #elif defined(MYLIB_OS_LINUX)
       LinuxSpecificFunction();
   #endif
   ```

4. **调试诊断**

   ```c
   MYLIB_ASSERT(p != NULL);
   MYLIB_LOG("Buffer size: %zu", size);
   ```

---

#### **与普通宏的本质区别**

| 特性         | 传统宏            | 本设计宏         |
| ------------ | ----------------- | ---------------- |
| **可读性**   | `#define MAX 100` | `MYLIB_MAX_SIZE` |
| **安全性**   | 无参数保护        | 全参数括号化     |
| **可维护性** | 分散定义          | 集中管理版本控制 |
| **调试支持** | 无上下文信息      | 带文件/行号诊断  |

