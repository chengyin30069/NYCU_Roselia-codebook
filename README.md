# NYCU_hwh

Codebook for ICPC team NYCU_hwh from National Yang Ming Chiao Tung University.

## Members

- [H1de_on_bruH]()
- [Howard]()
- [wym]()


## Codebook Compile

0. Install & Start docker (optionally install docker-buildx in archlinux).
1. Build the docker image (only need to run once): `docker build -t archlatex .` 
2. Compile the codebook: `docker run -v ".:/work" --rm -u "$(id -u):$(id -g)" archlatex`
