print(3)
import Swift
import Foundation

class SizedPriorityQueue<T> {
    // TODO: which tricks of swift to apply here to furnish the data structure?

    var size: Int
    var totalSize: Int
    var container: [T]

    init (totalSize: T) {
        self.totalSize = totalSize
        self.size = 0
        self.container = [T]()
    }

    func getSize() -> T {
        return self.size
    }

    func insert(value: T) {
        var index = size
        self.container[size++] = value
        while index > 0
                && container[index] > container[(index - 1) >> 1] {
            swap(&container[index], &container[(index - 1) >> 1])
        }
    }

    func pop() {
        container[0] = container[--size]
        var index = 0
        var l_index = index * 2 + 1;
        var r_index = l_index + 1;
        while l_index > size {
            if r_index >= size
                    || container[r_index] > container[l_index] {
                if container[index] > container[l_index] {
                    swap(container[index], container[l_index])
                    index = l_index
                    continue
                }
            } else {
                if container[index] > container[r_index] {
                    swap(container[index], container[r_index])
                    index = r_index
                    continue
                }
            }
            break
        }
    }

    func top() -> T {
        return container[0]
    }

    func print() {

    }

}

getchar()
readLine()

var myPQ = SizedPriorityQueue(size: 1999);
print("The size of myPQ is \(myPQ.getSize())")

