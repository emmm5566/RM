//1. 在session3_ws/src/learn_pkg/include下
// git clone https://gitee.com/fishros/cpp-httplib.git    
//直接使用HTTPS地址克隆，无需身份验证配置，无需配置SSH密钥
//2. 在CMakeLists.txt中 添加include_directories(include)
//3. 在代码中 加#include"cpp-httplib/httplib.h"

#include <iostream>
#include <thread> //多线程
#include <chrono> //时间
#include <functional> //函数包装器
#include "cpp-httplib/httplib.h" //下载

class Download 
{
public:
    void download(const std::string& host, const std::string& path,
        const std::function<void(const std::string&, const std::string&)> callback_word_count) 
    {
        //打印线程编号
        std::cout << "线程" << std::this_thread::get_id() << std::endl; 
        //创建客户端
        httplib::Client client(host);
        auto response = client.Get(path);
        if(response && response->status==200) { //http规定，请求响应状态码为200为成功响应
            callback_word_count(path, response->body);
        } else {
            std::cout << "下载失败 " << path << std::endl;
        } 
    };
    void start_download(const std::string& host, const std::string& path,
        const std::function<void(const std::string&, const std::string&)> callback_word_count) 
    {
        //创建线程 (目标函数, 参数列表)
        //需要按函数包装器的方法传函数，这是一个成员函数需要绑定
        auto download_fun = std::bind(&Download::download, this, 
            std::placeholders::_1, std::placeholders::_2, std::placeholders::_3);
        std::thread thread(download_fun, host, path, callback_word_count);

        // //c++中线程创建好后会立刻运行
        // thread.detach();  //把创建的线程分离出来

        // 使用join来确保主线程会等待子线程完成
        thread.join();  // 等待线程完成
    };

private:

};

int main() 
{
    auto d = Download();
    auto word_count = [](const std::string& path, const std::string& result) -> void {
        std::cout << "下载完成" << path << " : " << result.length() << " -> " << result.substr(0, 5) << std::endl;
    };

    // httpbin.org是一个HTTP测试网站，提供一个用于调试HTTP请求和响应的API
    d.start_download("http://httpbin.org", "/ip", word_count); // 小文件测试

    // std::this_thread::sleep_for(std::chrono::milliseconds(1000*10)); //休眠10s
    return 0;
}





//潜在问题：当在main函数中启动了线程后，由于thread.detach()分离了线程，主线程无法等待子线程的执行，因此很可能主线程在子线程执行前就结束了
//解决方法：
//（1）为了避免这个问题，可以将主线程的休眠时间延长std::this_thread::sleep_for()，确保子线程有足够时间执行
//（2）thread.detach()和std::this_thread::sleep_for()，换成thread.join()
