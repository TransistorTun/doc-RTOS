# RTOS Fundamental

## Multitasking

Kernel là thành phần cốt lõi trong một hệ điều hành. Các hệ điều hành như Linux sử dụng Kernels cho phép người dùng truy cập vào máy tính dường như đồng thời. Nhiều người dùng có thể thực hiện nhiều chương trình dường như đồng thời.

Mỗi chương trình thực thi là 1 Task (hoặc là một Thread) dưới sự kiểm soát của Hệ Điều Hành. Nếu một hệ điều hành thực thi được nhiều Task thì người ta gọi là đa nhiệm (**MultiTasking**)

Việc sử dụng một hệ điều hành đa nhiệm có thể đơn giản hóa thiết kế của một phần mềm phức tạp.
  * Multitasking và các liên lạc của inter-task cho phép biến các ứng dụng phức tạp thành các tác vụ nhỏ hơn, dễ quản lý hơn
  * Việc chia nhỏ sẽ giúp test phần mềm dễ dàng hơn, chia nhỏ công việc trong nhóm và tái sử dụng code
  * Các timing phức tạp, những chi tiết liên tục có thể đưa ra khỏi code của ứng dụng và trở thành nhiệm vụ của của hệ điều hành

### Multitasking và Concurrency

Một bộ xử lý thông thường chỉ có thể thực hiện được một Task trong một thời điểm cụ thể - nhưng mà bằng cách chuyển đổi nhanh chóng giữa các Task, một hệ điều hành có thể làm cho chúng xuất hiện như đang thực thi đồng thời.

![Alt text](image-1.png)

## Scheduling

Scheduler là một phần của Kernel chịu trách nhiệm quyết định tác vụ nào sẽ được thực thi tại bất kì thời điểm cụ thể nào. Kernel có thể Suspend và Resume một tác vụ nhiều lần trong suốt quãng thời gian tác vụ đó tồn tại

Chính sách scheduling là thuật toán được scheduler sử dụng để quyết định xem Task nào sẽ được thực hiện ở thời điểm nào. Chính sách của non-realtime sẽ cho phép mỗi task có tỷ lệ công bằng về thời gian của bộ xử lý.

Ngoài việc bị Kernel Suspend một cách không tự nguyện thì một Task còn có thể tự Suspend. Nó sẽ thực hiện điều này nếu nó muốn delay (sleep) trong một khoảng thời gian cố định, hoặc chờ để tài nguyên sẵn sàng hoặc một sự kiện xảy ra. Các tác vụ bị chặn hoặc đang ngủ không thể thực thi và sẽ không được phân bố thời gian xử lý.

![Alt text](image-2.png)

* Tại (1) thì Task1 đang thực thi
* Tại (2) thì Kernel sẽ Suspend Task1
* Tại (3) thì Task2 Resume
* Trong khi Task2 đang được thực thi (4), nó khóa một thiết bị ngoại vi của bộ xử lý để có độc quyền riêng của nó
* Tại (5) Kernel Suspend Task2
* Tại (6) Resume Task3.
* Task3 cố gắng truy cập cùng một thiết bị ngoại vi của bộ vi xử lý (7), thấy được vi xử lý bị khóa nên Task3 bị Suspend.
* Tại (8) Kernel Resume Task1
  

## Context Switching

Khi mà một Task thực thi nó sử dụng bộ xử lý / các thanh ghi của vi điều khiển và truy cập vào RAM, ROM giống như bất kì chương trình nào khác. Các tài nguyên này (thanh ghi, stack,...) tạo nên **ngữ cảnh** thực thi tác vụ

![Alt text](image-3.png)

Một task là sự tuần tự của các dòng code - nó không biết khi nào nó bị Suspend (Swapped out hoặc là Switched out) hoặc là Resume (Swapped in hoặc là Switched in) bởi Kernel và thậm chí cũng không biết khi nào việc này xảy ra.

*Ví dụ:* Một Task bị Suspend ngay lập tức trước khi thực thi một lệnh tính tổng của 2 thanh ghi trong bộ xử lý. Khi mà task này bị Suspend thì các task khác sẽ hoạt động mà có thể thay đổi giá trị của các thanh ghi. Khi tiếp tục lại thì task không biết rằng các thanh ghi đã bị thay đổi và nếu nó sử dụng các thanh ghi đó thì phép cộng 2 thanh ghi sẽ cho kết quả không chính xác.

Để ngăn chặn lỗi sai này xảy ra thì điều cần thiết khi tiếp tục lại task là, task đó phải có ngữ cảnh giống với ngữ cảnh ngay trước khi tạm dừng. Kernel có trách nhiệm đảm bảo việc đó và cũng như là lưu lại ngữ cảnh của task khi Suspend. Khi mà task được tiếp tục lại thì ngữ cảnh đã được lưu sẽ được lấy ra bởi Kernel trước khi thực thi. 

***Quá trình lưu ngữ cảnh của một task đang bị Suspend và khôi phục ngữ cảnh của một tác vụ đang được tiếp tục gọi là chuyển đổi ngữ cảnh***    
**ĐÓ LÀ CONTEXT SWITCHING**


## Real Time Applications

Hệ điều hành real time đạt được đa nhiệm bằng cách sử dụng các nguyên tắc đó - nhưng mục tiêu của chúng rất khác so với các hệ thống non real time. Mục tiêu khác nhau thể hiện trong việc scheduling. Các hệ thống real time / hệ thống nhúng được thiết kế để cung cấp phản hồi kịp thời cho các sự kiện xảy ra trong thế giới thực.
Một sự kiện xảy ra ở thế giới thực thì cần một thời gian đáp ứng kịp lúc mà các hệ thống thời gian thực phải đáp ứng, RTOS scheduling phải đảm bảo thời gian đó được đáp ứng

Để đạt được mục tiêu thì đầu tiên các kĩ sư phần mềm phải sắp xếp thứ tự ưu tiên cho mỗi task. RTOS Scheduling sau đó đơn giản chỉ là đảm bảo rằng các task có mức ưu tiên cao nhất có thể thực thi là các task được cung cấp thời gian để xử lý. Điều này yêu cầu sự phân chia một cách "công bằng" thời gian của hệ thống giữa các task có cùng mức độ ưu tiên với nhau nếu chúng sẵn sàng chạy đồng thời.



