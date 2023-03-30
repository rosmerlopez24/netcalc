#include <argparse/argparse.hpp>
#include <asio/error_code.hpp>
#include <asio/ip/network_v4.hpp>
#include <bitset>
#include <iostream>
#include <limits>
#include <stdexcept>
#include <string>
#include <tabulate/table.hpp>

using namespace asio;
using namespace asio::ip;
using namespace tabulate;

/* Displays the ipv4 network information table */
auto show_network_table(const network_v4 &network) -> void;

/* Convert number to binary in dotted format */
template <typename T> auto to_binary(const T &value) -> std::string;

int main(int argc, char *argv[]) {
  // Create instance of parser for program
  argparse::ArgumentParser program{"netcalc", "v0.0.1"};

  // Added settings for program
  program.add_description(
      "Utility that calculates network address, netmask, network, broadcast, "
      "etc by given IP Address with CIRD Notation.");
  program.add_argument("address").help(
      "ip address with cird notation, example: 192.168.100.1/24");
  program.add_epilog("Written by Rosmer Lopez");

  // Parser arguments
  try {
    program.parse_args(argc, argv);
  } catch (std::runtime_error &error) {
    std::cerr << error.what() << std::endl;
    std::cerr << program;
    std::exit(1);
  }

  // Saves the error in the construction
  error_code error_make_network_v4{};

  // Get ip address from arguments
  const auto ip_address{program.get<std::string>("address")};

  // Build network_v4 from ip address
  const network_v4 network{make_network_v4(ip_address, error_make_network_v4)};

  // In case of error, it displays it and exits
  if (error_make_network_v4) {
    std::cerr << error_make_network_v4.message() << std::endl;
    std::cerr << program;
    std::exit(1);
  }

  // Display network
  show_network_table(network);
  return 0;
}

auto show_network_table(const network_v4 &network) -> void {
  Table data{};

  /* Set data to table */
  data.add_row({"Address", network.address().to_string(),
                to_binary(network.address().to_uint())});
  data.add_row({"Netmask", network.netmask().to_string(),
                to_binary(network.netmask().to_uint())});
  data.add_row({"Network", network.canonical().to_string(),
                to_binary(network.network().to_uint())});
  data.add_row({"Broadcast", network.broadcast().to_string(),
                to_binary(network.broadcast().to_uint())});
  data.add_row({"Start range", network.hosts().begin()->to_string(),
                to_binary(network.hosts().begin()->to_uint())});
  data.add_row({"End range", (--network.hosts().end())->to_string(),
                to_binary((--network.hosts().end())->to_uint())});
  data.add_row({"Hosts", std::to_string(network.hosts().size())});

  /* Set format to table */
  data.column(0)
      .format()
      .font_align(FontAlign::center)
      .font_style({FontStyle::bold})
      .font_color(Color::blue);

  /* Displaying using overload operator */
  std::cout << data << std::endl;
}

template <typename T> auto to_binary(const T &value) -> std::string {
  /* Convert to binary */
  std::string container{};
  if (value > 0) {
    container = std::bitset<std::numeric_limits<T>::digits>(value).to_string();
  }

  /* Format to dotted */
  std::string result{};
  for (std::string::size_type index{0}; const auto &element : container) {
    result.push_back(element);
    if ((index + 1) % 8 == 0 && index != container.length() - 1) {
      result.push_back('.');
    }
    ++index;
  }
  return result;
}
