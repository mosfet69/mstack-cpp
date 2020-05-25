#pragma once
#include <array>
#include <algorithm>
#include "utils.hpp"

namespace mstack{

struct mac_addr_t {
private:
    std::array<uint8_t, 6> mac;

public:
    mac_addr_t() = default;
    ~mac_addr_t() = default;
    mac_addr_t(const mac_addr_t& other)
    {
        std::copy(std::begin(other.mac), std::end(other.mac), std::begin(mac));
    }
    
    mac_addr_t(mac_addr_t&& other)
    {
        std::swap(mac, other.mac);
    }
    mac_addr_t& operator=(const mac_addr_t& other)
    {
        if (this != &other) {
            std::copy(std::begin(other.mac), std::end(other.mac), std::begin(mac));
        }
    }

    mac_addr_t& operator=(mac_addr_t&& other)
    {
        std::swap(mac, other.mac);
    };

    mac_addr_t(std::array<uint8_t, 6> other){
        for(int i = 0; i < 6; i++){
            mac[i] = other[i];
        }
    }

    mac_addr_t(uint8_t other[6]){
        for(int i = 0; i < 6; i++){
            mac[i] = other[i];
        }
    }
    mac_addr_t(std::string mac_addr_t)
    {
        for (int i = 0; i < 17; i += 3) {
            std::string tmp = mac_addr_t.substr(i, 2);
            uint8_t tmp_int = std::stoi(tmp, 0, 16);
            mac[i / 3] = tmp_int;
        }
    };

    void consume(uint8_t*& ptr){
        for(int i = 0; i < 6; i++){
            mac[i] = util::consume<uint8_t>(ptr);
        }
    }

    void produce(uint8_t*& ptr){
        for(int i = 0; i < 6; i++){
            uint8_t tmp = mac[i];
            util::produce<uint8_t>(ptr, tmp);
        }
    }
    static constexpr size_t size() {
       return 6;
    }
    friend std::ostream& operator<<(std::ostream& out, const mac_addr_t& m)
    {
        using u = uint32_t;
        out << util::format("%02X:%02X:%02X:%02X:%02X:%02X",
            u(m.mac[0]), u(m.mac[1]), u(m.mac[2]), u(m.mac[3]), u(m.mac[4]), u(m.mac[5]));
        return out;
    }
};

}