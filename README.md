# Sleeping-Barber-problems-with-multiple-barbers-

Sleeping Barber Problem Solution in C
The sleeping barber dilemma was first posed by Dijkstra in 1965. This issue is based on a fictitious situation in which there is a single barber at a barbershop. The waiting area and the workroom are separated in the barbershop. Customers can wait in the waiting area on n seats; however there is only one barber chair in the workroom.

Inter Process Communication
While a cooperating process might be impacted by other processes that are running, an independent process is unaffected by the execution of other processes. Although it is possible to assume that processes operating independently will function extremely effectively, there are really numerous circumstances in which co-operative nature may be used to boost computing speed, ease, and flexibility. Processes can interact with one another and coordinate their operations through a technique called inter-process communication (IPC). These processes' communication with one another might be thought of as a means of cooperation.

Problem:

The problem is based on a fictitious barbershop with just one barber, which is a problem. There is a barbershop with one barber, one chair for the barber, and n seats to wait for clients to sit in the chair, if any.

If there isn't a client, the barber will fall asleep on his own chair.
He needs to rouse the barber when a client shows up.
The remaining customers can either wait if there are empty seats in the waiting area or they can leave if there are no empty chairs when there are numerous clients and the barber is cutting a customer's hair.
Solution:

Three semaphores are used in the solution to this issue. The first counts the number of customers in the waiting area and is for the customer (customer in the barber chair is not included because he is not waiting). The second mutex is used to give the mutual exclusion necessary for the process to operate, and the barber 0 or 1 is used to determine if the barber is idle or working. The client keeps a record of how many customers are currently waiting in the waiting area, and when that number equals the number of chairs in the area, the next customer exits the barbershop.

The procedure barber is carried out when the barber arrives in the morning, forcing him to block on the semaphore clients since it is originally 0. The barber then retires to bed till the first client arrives.
