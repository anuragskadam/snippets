class Heap:
    """Written by Clocky"""

    def __init__(self, list_in: list = [], key=None) -> None:
        self.list = list(list_in)
        self.key = (lambda x: x) if (key is None) else key
        self._default_key = key is None
        self._heapify_list()

    def __len__(self):
        return len(self.list)

    def __repr__(self) -> str:
        return (
            (f"Heap({self.list})" if self else "Heap()")
            if self._default_key
            else (
                f"Heap({self.list}, key={self.key.__name__})"
                if self
                else f"Heap(key={self.key.__name__})"
            )
        )

    def __contains__(self, item):
        return item in self.list

    def __iter__(self):
        return iter(self.list)

    def insert(self, element):
        self.list.append(element)
        self._heapify_up()

    def pop(self):
        if len(self) > 1:
            ans = self.list[0]
            self.list[0] = self.list.pop()
            self._heapify_down()
            return ans
        elif len(self) == 1:
            return self.list.pop()
        else:
            raise IndexError("pop() from empty Heap")

    def top(self):
        if self:
            return self.list[0]
        else:
            raise IndexError("top() from empty Heap")

    @staticmethod
    def _left(idx):
        return 2*idx + 1
    
    @staticmethod
    def _right(idx):
        return 2*idx + 2

    @staticmethod
    def _par(idx):
        return (idx - 1) // 2

    def _heapify_down(self, idx: int = 0):
        left = self._left(idx)
        right = self._right(idx)

        while left < len(self):
            min_child_val = (
                min(self.key(self.list[left]), self.key(self.list[right]))
                if right < len(self)
                else self.key(self.list[left])
            )
            if min_child_val < self.key(self.list[idx]):
                if self.key(self.list[left]) == min_child_val:
                    self._swap(idx, left)
                    idx = left
                else:
                    self._swap(idx, right)
                    idx = right
                left = self._left(idx)
                right = self._right(idx)
            else:
                break
    
    def _heapify_up(self, idx: int = None):
        idx = idx if idx is not None else (len(self) - 1)
        par = self._par(idx)
        while idx and self.key(self.list[par]) > self.key(self.list[idx]):
            self._swap(par, idx)
            idx = par
            par = self._par(idx)

    def _heapify_list(self):
        for idx in range(self._par(len(self)-1), -1, -1):
            self._heapify_down(idx)

    def _swap(self, i1: int, i2: int):
        self.list[i1], self.list[i2] = self.list[i2], self.list[i1]


if __name__ == "__main__":
    # demo
    h = Heap([3, 4, 5, 2, 2, 6, 3, 2, 1, 3, 5, 2, 10])

    print(h)

    for i in range(len(h) + 3):
        print(h.pop(), h)
        if i == 5:
            h.insert(4.7)
            print("inserted 4.7", h)
        elif i == 6:
            h.insert(1)
            print("inserted 1", h)

