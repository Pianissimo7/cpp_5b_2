#include "MagicalContainer.hpp"


using namespace ariel;
using namespace std;

MagicalContainer::MagicalContainer() {
    this->container = vector<int>();
    this->primes = vector<int>();
}
MagicalContainer::~MagicalContainer() {
}
size_t MagicalContainer::find_placement_container(int n) {
    for (size_t i = 0 ; i < this->container.size() ; i++) {
        if (n < this->container[i]) {
            return i;
        }
    }
    return this->container.size();
}
size_t MagicalContainer::find_placement_primes(int n) {
    for (size_t i = 0 ; i < this->primes.size() ; i++) {
        if (n < this->primes[i]) {
            return i;
        }
    }
    return this->primes.size();
}
void MagicalContainer::addElement(int n) {
    size_t index_of_element = this->find_placement_container(n);
    if (index_of_element == this->container.size()) {
        this->container.push_back(n);
    }
    else {
        this->container.insert(this->container.begin() + (int)index_of_element, n);
    }
    if (is_prime(n)) {
        size_t index_of_prime_element = this->find_placement_primes(n);
        if (index_of_prime_element == this->primes.size()) {
            this->primes.push_back(n);
        }
        else {
            this->primes.insert(this->primes.begin() + (int)index_of_prime_element, n);
        }
    }
}
void MagicalContainer::removeElement(int n) {
    vector<int>::iterator it = find(this->container.begin(), this->container.end(), n);
    if (it == this->container.end()) {
        throw std::runtime_error("element was not found");
    }
    else {
        this->container.erase(it);
        if (this->is_prime(n)) {
            this->container.erase(find(this->primes.begin(), this->primes.end(), n));
        }
    }
}
int& MagicalContainer::get_at(size_t index) {
    return this->container[index];
}
int& MagicalContainer::prime_get_at(size_t index) {
    return this->primes[index];
}
size_t MagicalContainer::size() {
    return this->container.size();
}
size_t MagicalContainer::primes_size() {
    return this->primes.size();
}
bool MagicalContainer::is_prime(int n) {
    if (n <= 1) {
        return false;
    }
    if (n == 2 || n == 3) {
        return true;
    }
    for (int i = 2 ; i <= n/2 ; i++) {
        if (n % i == 0) {
            return false;
        }
    }
    return true;
}
vector<int> MagicalContainer::get_container() const {
    return this->container;
}
bool MagicalContainer::operator==(const MagicalContainer& other) const {
    return this->container == other.get_container();
}
bool MagicalContainer::operator!=(const MagicalContainer& other) const {
    return !(this->container == other.get_container());
}

int& MagicalContainer::Iterator::operator*() {
    return this->container.get_at(this->currentIndex);
}
size_t MagicalContainer::Iterator::get_currentIndex() const {
    return this->currentIndex;
}
MagicalContainer& MagicalContainer::Iterator::get_container() const {
    return this->container;
}

int& MagicalContainer::AscendingIterator::operator*() {
    return this->container.get_at(this->currentIndex);
}
MagicalContainer::AscendingIterator MagicalContainer::AscendingIterator::begin() {
    MagicalContainer::AscendingIterator it(this->container);
    return it;
}
MagicalContainer::AscendingIterator MagicalContainer::AscendingIterator::end() {
    size_t temp = this->currentIndex;
    this->currentIndex = this->container.size();
    MagicalContainer::AscendingIterator it(*this);
    this->currentIndex = temp;

    return it;
}
MagicalContainer::AscendingIterator& MagicalContainer::AscendingIterator::operator++() {
    if (this->currentIndex == this->container.size()) {
        throw std::runtime_error("element was not found");
    }
    this->currentIndex++;
    return *this;
}
bool MagicalContainer::AscendingIterator::operator!=(const MagicalContainer::AscendingIterator& other) const {
    return !(*this == other);
}
bool MagicalContainer::AscendingIterator::operator==(const MagicalContainer::AscendingIterator& other) const {
    return this->container == other.get_container() && this->currentIndex == other.get_currentIndex();
}
bool MagicalContainer::AscendingIterator::operator<(const MagicalContainer::AscendingIterator& other) const {
    return this->container == other.get_container() && this->currentIndex < other.get_currentIndex();
}
bool MagicalContainer::AscendingIterator::operator>(const MagicalContainer::AscendingIterator& other) const {
    return !(*this < other) && *this != other;
}
MagicalContainer::AscendingIterator& MagicalContainer::AscendingIterator::operator=(const MagicalContainer::AscendingIterator& other) {
    if (this->container != other.container) {
        throw std::runtime_error("cannot assign an iterator which has a different container");
    }
    if (this != &other) { 
        this->container = other.container;
        this->currentIndex = other.currentIndex;
    }
    return *this;
}

int& MagicalContainer::SideCrossIterator::operator*() {
    size_t index = currentIndex / 2;
    if (this->currentIndex % 2 == 0) {
        return this->container.get_at(index);
    }
    else {
        return this->container.get_at(this->container.size() - 1 - index);
    }
    
}
MagicalContainer::SideCrossIterator MagicalContainer::SideCrossIterator::begin() {
    MagicalContainer::SideCrossIterator it(this->container);
    return it;
}
MagicalContainer::SideCrossIterator MagicalContainer::SideCrossIterator::end() {
    size_t temp = this->currentIndex;
    this->currentIndex = this->container.size();
    MagicalContainer::SideCrossIterator it(*this);
    this->currentIndex = temp;

    return it;
}
MagicalContainer::SideCrossIterator& MagicalContainer::SideCrossIterator::operator++() {
    if (this->currentIndex == this->container.size()) {
        throw std::runtime_error("element was not found");
    }
    this->currentIndex++;
    return *this;
}
bool MagicalContainer::SideCrossIterator::operator!=(const MagicalContainer::SideCrossIterator& other) const {
    return !(*this == other);
}
bool MagicalContainer::SideCrossIterator::operator==(const MagicalContainer::SideCrossIterator& other) const {
    return this->container == other.get_container() && this->currentIndex == other.get_currentIndex();
}
bool MagicalContainer::SideCrossIterator::operator<(const MagicalContainer::SideCrossIterator& other) const {
    return this->container == other.get_container() && this->currentIndex < other.get_currentIndex();
}
bool MagicalContainer::SideCrossIterator::operator>(const MagicalContainer::SideCrossIterator& other) const {
    return !(*this < other) && *this != other;
}
MagicalContainer::SideCrossIterator& MagicalContainer::SideCrossIterator::operator=(const MagicalContainer::SideCrossIterator& other) {
    if (this->container != other.container) {
        throw std::runtime_error("cannot assign an iterator which has a different container");
    }
    if (this != &other) { 
        this->container = other.container;
        this->currentIndex = other.currentIndex;
    }
    return *this;
}

int& MagicalContainer::PrimeIterator::operator*() {
    return this->container.prime_get_at(this->currentIndex);
}
MagicalContainer::PrimeIterator MagicalContainer::PrimeIterator::begin() {
    MagicalContainer::PrimeIterator it(this->container);
    return it;
}
MagicalContainer::PrimeIterator MagicalContainer::PrimeIterator::end() {
    size_t temp = this->currentIndex;
    this->currentIndex = this->container.primes_size();
    MagicalContainer::PrimeIterator it(*this);
    this->currentIndex = temp;

    return it;
}
MagicalContainer::PrimeIterator& MagicalContainer::PrimeIterator::operator++() {
    if (this->currentIndex == this->container.primes_size()) {
        throw std::runtime_error("element was not found");
    }
    this->currentIndex++;
    return *this;
}
bool MagicalContainer::PrimeIterator::operator!=(const MagicalContainer::PrimeIterator& other) const {
    return !(*this == other);
}
bool MagicalContainer::PrimeIterator::operator==(const MagicalContainer::PrimeIterator& other) const {
    return this->container == other.get_container() && this->currentIndex == other.get_currentIndex();
}
bool MagicalContainer::PrimeIterator::operator<(const MagicalContainer::PrimeIterator& other) const {
    return this->container == other.get_container() && this->currentIndex < other.get_currentIndex();
}
bool MagicalContainer::PrimeIterator::operator>(const MagicalContainer::PrimeIterator& other) const {
    return !(*this < other) && *this != other;
}
MagicalContainer::PrimeIterator& MagicalContainer::PrimeIterator::operator=(const MagicalContainer::PrimeIterator& other) {
    if (this->container != other.container) {
        throw std::runtime_error("cannot assign an iterator which has a different container");
    }
    if (this != &other) { 
        this->container = other.container;
        this->currentIndex = other.currentIndex;
    }
    return *this;
}
