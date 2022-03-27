/* Примечание
 * Те из вас, кто уже хорошо знаком с С++, могли удивиться,
 * почему в нашем решении operator= имеет тип void, а не SimpleVector&,
 * как это обычно принято при перегрузке оператора присваивания.
 * Всё очень просто — мы стараемся быть последовательными в наших материалах и не использовать те вещи,
 * о которых мы не рассказывали. В материалах «Красного пояса» не нашлось места для рассказа об указателе this,
 * поэтому мы не используем его в своём решении.
*/
template <typename T>
class SimpleVector {
public:
  SimpleVector() = default;
  explicit SimpleVector(size_t size);
  SimpleVector(const SimpleVector& rhs);
  ~SimpleVector();

  void operator=(const SimpleVector& rhs) {
    if (rhs.size <= capacity) {
      // У нас достаточно памяти - просто копируем элементы
      copy(rhs.begin(), rhs.end(), begin());
      size = rhs.size;
    } else {
      // Это так называемая идиома copy-and-swap.
      // Мы создаём временный вектор с помощью
      // конструктора копирования, а затем обмениваем его поля со своими.
      // Так мы достигаем двух целей:
      //  - избегаем дублирования кода в конструкторе копирования
      //    и операторе присваивания
      //  - обеспечиваем согласованное поведение конструктора копирования
      //    и оператора присваивания
      SimpleVector<T> tmp(rhs);
      swap(tmp.data, data);
      swap(tmp.size, size);
      swap(tmp.capacity, capacity);
    }
  }

  T& operator[](size_t index);

  T* begin();
  T* end();

  const T* begin() const;
  const T* end() const;

  size_t Size() const;
  size_t Capacity() const;
  void PushBack(const T& value);

private:
  T* data = nullptr;
  size_t size = 0;
  size_t capacity = 0;
};
