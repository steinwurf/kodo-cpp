// Copyright Steinwurf ApS 2016.
// Distributed under the "STEINWURF RESEARCH LICENSE 1.0".
// See accompanying file LICENSE.rst or
// http://www.steinwurf.com/licensing

#include <cassert>
#include <csignal>
#include <cstdint>
#include <cstdio>
#include <cstdlib>
#include <vector>

#ifdef _WIN32
    #include <winsock2.h>
    typedef int socklen_t;
#else
    #include <sys/socket.h>
    #include <netinet/in.h>
    #include <arpa/inet.h>
    #include <netdb.h>
    #include <unistd.h>
#endif

#include <sys/types.h>

#include <kodocpp/kodocpp.hpp>

// Count the total number of packets received in order to decode
unsigned int rx_packets;

static void exit_on_sigint(int sig)
{
    (void) sig;
    printf("\nTotal number of received packets: %d\n", rx_packets);
    exit(0);
}

int main(int argc, char* argv[])
{
    // Variables needed for the network / socket usage
    int32_t socket_descriptor = 0;
    int32_t return_code = 0;
    int32_t bytes_received = 0;
    socklen_t remote_address_size;
    struct sockaddr_in remote_address;
    struct sockaddr_in local_address;

    // Initialize winsock if on Windows
#ifdef _WIN32
    WORD versionWanted = MAKEWORD(1, 1);
    WSADATA wsaData;

    return_code = WSAStartup(versionWanted, &wsaData);

    if (return_code != 0)
    {
        // Tell the user that we could not find a usable
        // Winsock DLL.
        printf("WSAStartup failed with error: %d\n", return_code);
        exit(1);
    }
#endif

    // Initialize global variables
    rx_packets = 0;

    if (argc < 3)
    {
        printf("usage: %s <port> <symbols>\n", argv[0]);
        exit(1);
    }

    // Socket creation
    socket_descriptor = socket(AF_INET, SOCK_DGRAM, 0);
    if (socket_descriptor < 0)
    {
        printf("%s: cannot open socket \n", argv[0]);
        exit(1);
    }

    // Bind local server port
    local_address.sin_family = AF_INET;
    local_address.sin_addr.s_addr = htonl(INADDR_ANY);
    local_address.sin_port = htons(atoi(argv[1]));
    return_code = bind(socket_descriptor, (struct sockaddr*) &local_address,
                       sizeof(local_address));

    if (return_code < 0)
    {
        printf("%s: cannot bind port number %d \n", argv[0], atoi(argv[1]));
        exit(1);
    }

    // Install signal handler
    signal(SIGINT, exit_on_sigint);

    // Variables needed for the coding
    uint32_t symbols = atoi(argv[2]);
    uint32_t symbol_size = 160;

    // Initialize the factory with the chosen symbols and symbol size
    kodocpp::decoder_factory decoder_factory(
        kodocpp::codec::on_the_fly,
        kodocpp::field::binary8,
        symbols, symbol_size);

    kodocpp::decoder decoder = decoder_factory.build();

    // Create the buffer needed for the payload
    uint32_t payload_size = decoder.payload_size();
    std::vector<uint8_t> payload(payload_size);

    // Set the storage for the decoder
    std::vector<uint8_t> data_out(decoder.block_size());
    decoder.set_mutable_symbols(data_out.data(), decoder.block_size());

    // Keeps track of which symbols have been decoded
    std::vector<bool> decoded(symbols, false);

    printf("Waiting for data on UDP port %u\n", atoi(argv[1]));

    // Receiver loop
    while (!decoder.is_complete())
    {
        // Receive message
        remote_address_size = sizeof(remote_address);

        bytes_received = recvfrom(
            socket_descriptor, (char*)payload.data(), payload_size, 0,
            (struct sockaddr*) &remote_address, &remote_address_size);

        if (bytes_received < 0)
        {
            printf("%s: recvfrom error %d\n", argv[0], bytes_received);
            fflush(stdout);
            continue;
        }

        // Print received message
        printf("UDP packet received from %s:%u : %d bytes\n",
               inet_ntoa(remote_address.sin_addr),
               ntohs(remote_address.sin_port), bytes_received);

        ++rx_packets;

        // Packet got through - pass that packet to the decoder
        decoder.read_payload(payload.data());

        if (decoder.has_partial_decoding_interface() &&
            decoder.is_partially_complete())
        {
            for (uint32_t i = 0; i < decoder.symbols(); ++i)
            {
                if (!decoded[i] && decoder.is_symbol_uncoded(i))
                {
                    // Update that this symbol has been decoded,
                    // in a real application we could process that symbol
                    printf("Symbol %d was decoded\n", i);
                    decoded[i] = true;
                }
            }
        }
    }

    printf("Data decoded!\n");

    return 0;
}
