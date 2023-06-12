#include <vector>
#include <stdexcept>

namespace ariel {
    class MagicalContainer {
        private:
            std::vector<int> container;
            std::vector<int> primes;
            bool is_prime(int n);
        public:
            MagicalContainer();
            ~MagicalContainer();
            size_t find_placement_container(int n);
            size_t find_placement_primes(int n);
            void addElement(int n);
            void removeElement(int n);
            int& get_at(size_t index);
            int& prime_get_at(size_t index);
            size_t size();
            size_t primes_size();
            std::vector<int> get_container() const;
            bool operator==(const MagicalContainer& other) const;
            bool operator!=(const MagicalContainer& other) const;

            class Iterator {
                protected:
                    MagicalContainer& container; // Reference to the container
                    size_t currentIndex; // Current index of the iterator
                public:
                    Iterator(MagicalContainer& cont) : currentIndex(0), container(cont) {}
                    size_t get_currentIndex() const;
                    MagicalContainer& get_container() const;
                    // Overload the * operator to get the value at the current index
                    virtual int& operator*();
            };
            class AscendingIterator : public Iterator {
                private:

                public:
                    AscendingIterator(MagicalContainer& cont) : Iterator(cont) {}
                    AscendingIterator(AscendingIterator& other) : Iterator(other.container) {
                        this->currentIndex = other.currentIndex;
                    }
                    // Function to get the iterator to the beginning of the container
                    AscendingIterator begin();

                    // Function to get the iterator to the end of the container
                    AscendingIterator end();
                    
                    virtual int& operator*() override;

                    // Overload the ++ operator to move the iterator to the next index
                    AscendingIterator& operator++();

                    // Overload the != operator to check if two iterators are not equal
                    bool operator!=(const AscendingIterator& other) const;
                    bool operator==(const AscendingIterator& other) const;
                    bool operator<(const AscendingIterator& other) const;
                    bool operator>(const AscendingIterator& other) const;
                    AscendingIterator& operator=(const AscendingIterator& other);
            };
            class SideCrossIterator : public Iterator {
                private:
                public:
                    SideCrossIterator(MagicalContainer& cont) : Iterator(cont) {}
                    SideCrossIterator(SideCrossIterator& other) : Iterator(other.container) {
                        this->currentIndex = other.currentIndex;
                    }
                    // Function to get the iterator to the beginning of the container
                    SideCrossIterator begin();

                    // Function to get the iterator to the end of the container
                    SideCrossIterator end();

                    virtual int& operator*() override;

                    // Overload the ++ operator to move the iterator to the next index
                    SideCrossIterator& operator++();

                    // Overload the != operator to check if two iterators are not equal
                    bool operator!=(const SideCrossIterator& other) const;
                    bool operator==(const SideCrossIterator& other) const;
                    bool operator<(const SideCrossIterator& other) const;
                    bool operator>(const SideCrossIterator& other) const;
                    SideCrossIterator& operator=(const SideCrossIterator& other);
            };
            class PrimeIterator : public Iterator {
                private:
                public:
                    PrimeIterator(MagicalContainer& cont) : Iterator(cont) {}
                    PrimeIterator(PrimeIterator& other) : Iterator(other.container) {
                        this->currentIndex = other.currentIndex;
                    }
                    // Function to get the iterator to the beginning of the container
                    PrimeIterator begin();

                    // Function to get the iterator to the end of the container
                    PrimeIterator end();

                    virtual int& operator*() override;

                    // Overload the ++ operator to move the iterator to the next index
                    PrimeIterator& operator++();

                    // Overload the != operator to check if two iterators are not equal
                    bool operator!=(const PrimeIterator& other) const;
                    bool operator==(const PrimeIterator& other) const;
                    bool operator<(const PrimeIterator& other) const;
                    bool operator>(const PrimeIterator& other) const;
                    PrimeIterator& operator=(const PrimeIterator& other);
            };
    };
}