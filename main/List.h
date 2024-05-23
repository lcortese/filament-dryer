class List {
  const String* items;
  const uint8_t itemsLength;
  static const uint8_t PAGE_LENGTH = 2;
  String range[PAGE_LENGTH];

  public:
    List(
      const String* itemsParam,
      const uint8_t itemsLengthParam
    ) :
      items(itemsParam),
      itemsLength(itemsLengthParam) {
    }

    uint8_t selectedIndex = 0;

    String* getItems() {
      uint8_t page = selectedIndex / PAGE_LENGTH;
      uint8_t listIndex = itemsLength > PAGE_LENGTH && selectedIndex + 1 == itemsLength
        ? itemsLength - PAGE_LENGTH
        : page * PAGE_LENGTH;

      for (uint8_t i = 0; i < PAGE_LENGTH; i++) {
        listIndex += i;
        if (listIndex < itemsLength) {
          range[i] = selectedIndex == listIndex ? ">" + items[listIndex] : " " + items[listIndex];
        } else {
          range[i] = "";
        }
      }

       return range;
    }
};
