String padStart(String str, size_t length) {
  const size_t strLength = str.length();
  if (strLength >= length) {
    return str;
  }
  
  String paddedStr;
  for (size_t i = 0; i < length - strLength; ++i) {
    paddedStr += "0";
  }
  paddedStr += str;
  return paddedStr;
}