all: oneway-udp-ipv4 oneway-udp-ipv6 twoway-udp-ipv4 twoway-udp-ipv6 twoway-tcp-ipv4 twoway-tcp-ipv6

oneway-udp-ipv4:
	gcc ./udp_oneway_ipv4/client/oneway-udp-client.c -o ./udp_oneway_ipv4/client/oneway-udp-client.triglia
	gcc ./udp_oneway_ipv4/server/oneway-udp-server.c -o ./udp_oneway_ipv4/server/oneway-udp-server.triglia

oneway-udp-ipv6:
	gcc ./udp_oneway_ipv6/client/oneway-udp-client.c -o ./udp_oneway_ipv6/client/oneway-udp-client.triglia
	gcc ./udp_oneway_ipv6/server/oneway-udp-server.c -o ./udp_oneway_ipv6/server/oneway-udp-server.triglia

twoway-tcp-ipv4: 
	gcc ./tcp_twoway_ipv4/client/twoway-tcp-client.c -o ./tcp_twoway_ipv4/client/twoway-tcp-client.triglia
	gcc ./tcp_twoway_ipv4/server/twoway-tcp-server.c -o ./tcp_twoway_ipv4/server/twoway-tcp-server.triglia

twoway-tcp-ipv6: 
	gcc ./tcp_twoway_ipv6/client/twoway-tcp-client.c -o ./tcp_twoway_ipv6/client/twoway-tcp-client.triglia
	gcc ./tcp_twoway_ipv6/server/twoway-tcp-server.c -o ./tcp_twoway_ipv6/server/twoway-tcp-server.triglia

twoway-udp-ipv4:
	gcc ./udp_twoway_ipv4/client/twoway-udp-client.c -o ./udp_twoway_ipv4/client/twoway-udp-client.triglia
	gcc ./udp_twoway_ipv4/server/twoway-udp-server.c -o ./udp_twoway_ipv4/server/twoway-udp-server.triglia

twoway-udp-ipv6:
	gcc ./udp_twoway_ipv6/client/twoway-udp-client.c -o ./udp_twoway_ipv6/client/twoway-udp-client.triglia
	gcc ./udp_twoway_ipv6/server/twoway-udp-server.c -o ./udp_twoway_ipv6/server/twoway-udp-server.triglia

clean:
	find . -name *.triglia -delete
	find . -name *.out -delete
