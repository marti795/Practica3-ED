template <class T>
class Tuple {
private:
    T line;
    T position;
public:
    Tuple(const T line, const T position);
    T getLine() const;
    T getPosition() const;
    void setLine(T line);
    void setPosition(T position);
    bool operator<(const Tuple<T>& other) const;
    bool operator==(const Tuple<T>& other) const;
};

template <class T>
Tuple<T>::Tuple(const T line, const T position){
    this->line = line;
    this->position = position;
}

template <class T>
T Tuple<T>::getLine() const{
    return line;
}

template <class T>
T Tuple<T>::getPosition() const{
    return position;
}

template <class T>
void Tuple<T>::setLine(T line){
    this->line = line;
}

template <class T>
void Tuple<T>::setPosition(T position){
    this->position = position;
}

template <class T>
bool Tuple<T>::operator<(const Tuple& other) const {
    if(line == other.line){
        return position < other.position;
    } 
    return line < other.line;
}

template <class T>
bool Tuple<T>::operator==(const Tuple& other) const {
    return line == other.line && position == other.position;
}