#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <vector>
#define CYBOZU_DONT_USE_OPENSSL
#include <cybozu/sha2.hpp>
#include <cybozu/test.hpp>
#include <cybozu/itoa.hpp>
#include <cybozu/atoi.hpp>
#include <cybozu/benchmark.hpp>

const struct Tbl {
	const char *out;
	const char *in;
} sha256Tbl[] = {
	{"e3b0c44298fc1c149afbf4c8996fb92427ae41e4649b934ca495991b7852b855", ""},
	{"ca978112ca1bbdcafac231b39a23dc4da786eff8147c4e72b9807785afee48bb", "a"},
	{"ba7816bf8f01cfea414140de5dae2223b00361a396177a9cb410ff61f20015ad", "abc"},
	{"52cbf04bed1f02f43d1caab3b63930c41010ecde117928724be789dac5fa18bb", "111111111111111111111111111111111111111111111111111111"},
	{"31f713cc40a632a9ce454b3029b727e9bb6d0eea11460f1d7818852c2565b9cd", "1111111111111111111111111111111111111111111111111111111"},
	{"9df2565d5163d54a49e6a8126bbd689614aeab8bc4aabfe69a8cb20975918ef2", "11111111111111111111111111111111111111111111111111111111"},
	{"dd6bc04f6a40788d771c73b4b8732a00a2c7e6b9520776265c31c0692326865c", "111111111111111111111111111111111111111111111111111111111"},
	{"c8c0cc46e25f2681e7fe5b795cf879fb05fcebf52f8fadd07c20b2e9ac75e0ba", "1111111111111111111111111111111111111111111111111111111111"},
	{"4fb703f4bf6bd112d2c8450ec4d66cc39456e75a4e10ab8ff25512b76eeb0b89", "11111111111111111111111111111111111111111111111111111111111"},
	{"70d36dedb311176c76ecd7f78d72340dbbaa364d23923239c8fda5b8c6ead201", "111111111111111111111111111111111111111111111111111111111111"},
	{"94dbfd746e995562d7f119e930564676e4bd1a6ec4ed3088222b09c76d88c87d", "1111111111111111111111111111111111111111111111111111111111111"},
	{"4d15cac6cec2d518728004ae016f33eb791f6b89edebd6c1e5eabd7e6f7826ad", "11111111111111111111111111111111111111111111111111111111111111"},
	{"60ac1bebb39f2d0bbd04fddaabe70270c3401c25e441a5a5bea291adef129d33", "111111111111111111111111111111111111111111111111111111111111111"},
	{"3138bb9bc78df27c473ecfd1410f7bd45ebac1f59cf3ff9cfe4db77aab7aedd3", "1111111111111111111111111111111111111111111111111111111111111111"},
	{"466680e1d9448572b0b27905731f290e591a52cfdfa2edf7a32169a3f6957af1", "11111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111"},
	{"3e8df35dfbeb228cfef6361ce98e975db153fdd9ea42522a581a015908d23e02", "111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111"},
	{"70ff2d4782bd27b199315e8c770c5b1bed76d9c8c262dbe03112c5cbb0d8bfb6", "1111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111"},
	{"965f77ba47402e8ffa4c594f116ffe1a99b6ed1f49341aa27a0fdebf5e18bd2a", "11111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111"},
	{"2c779adb8ae79df3965a9b8d62d6f64f05f4f82abef3bc8814f8374fac478582", "111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111"},
	{"4f58aea7c1c88ffaa58b1218e304add251deaf291bbaddcd095079bbca333338", "1111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111"},
	{"b922a0085535438943e1fecf51c9bc6c13f38977f779cfce9934f422239a8f4a", "11111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111"},
	{"cc46aec737b147f9b27f4aaa75cd58e62399d3b78cbed29f4ebb81d87734ad25", "111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111"},
	{"9c1debdbfea404f078d84ddaf6db820b3ad7f9700743ccbc78708578fc1bb53f", "1111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111"},
	{"52d844e0aa05175167543882659c5ecfb8bdf0bf3d0eefd3ab86643078cecf2b", "11111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111"},
	{"a174ccedaef055e5757f74f2bcc1a15e2e4065066b3ea9a34bdf89735bc6e10c", "111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111"},
	{"ab29b49e48726959285d8fe8e19f78b7e5bdb2c3184d99cb0890e69acc71bcc7", "1111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111"},
	{"ce232fb8cf607fe6e620da8f1c316a940dbe514f2f9f8d4212bbd74cf144dd9f", "11111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111"},
	{"8e73e16d08a10ff853f3816d10ba58821e1e9230973a7f320867bd0dde5b30c6", "111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111"},
	{"f4056698c3dc1d7352d38544c0435b17106ab359ebfb2b69ce6b69e30ee0e8cc", "1111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111"},
	{"0d0c64e24843a0fad6ed192c1f3cf7db7a02d8edb17b10808ef106fb1107bd06", "11111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111"},
	{"fc18053578d5dfb935474ff8cea71709cf0b0722799f7a98b0ef31276248386f", "111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111"},
	{"eef81ea912795a61bf2d3a29dc71faedd45157fe88220db7f92040aa9328cee6", "1111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111"},
	{"4ff5ac52aa16dbe3db447ea12d090c5bb6f1325aaaca5ee059b248a89f673972", "11111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111"},
	{"8dceb93f4389e8bd2bb482a145ed2a22172b6ddc9e4696cedf9f0da8008fc11c", "111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111"},
}, sha512Tbl[] = {
	{"cf83e1357eefb8bdf1542850d66d8007d620e4050b5715dc83f4a921d36ce9ce47d0d13c5d85f2b0ff8318d2877eec2f63b931bd47417a81a538327af927da3e", ""},
	{"1f40fc92da241694750979ee6cf582f2d5d7d28e18335de05abc54d0560e0f5302860c652bf08d560252aa5e74210546f369fbbbce8c12cfc7957b2652fe9a75", "a"},
	{"ddaf35a193617abacc417349ae20413112e6fa4e89a97ea20a9eeee64b55d39a2192992a274fc1a836ba3c23a3feebbd454d4423643ce80e2a9ac94fa54ca49f", "abc"},
	{"0bd33523145765f125a0c72556bb7657d4356c6c30fee54eca5f2de60687cbdb81e4b2f73350481e430208a6d703ec23f009881dd3793dbd2d67c21fde7259be", "111111111111111111111111111111111111111111111111111111"},
	{"70e4e22118ff7bfb284b8f691b95550e62f06c33103b5c7beb6e89ad29530aafd245cc3b00fb16f662d1b41fca5b62bc7dd0782951c3966f4cd101208e1e087f", "1111111111111111111111111111111111111111111111111111111"},
	{"fdb318fc2e4c7774cfe1586e4de0dcd3d315bde65c49074caed4d0b234fb78a38f920f49ec5c47a6cc53afd2523f730b4ab8c552f0a594b08fe20592d5fa63b7", "11111111111111111111111111111111111111111111111111111111"},
	{"63e1c7b0e145cca735a43a8cf4e900935313f635f8ce874739d8ed834ec795924cf6cc84fe41edcb822a32932450b8870a0e8342f47a694b3524af0b3b83c7a4", "111111111111111111111111111111111111111111111111111111111"},
	{"efdbc3fed2133cf1a80a40ee97517bc96763cc8021fd992e7f295caccf9a1422fc7ad6d0c87bdeb91540a35125335a95763430f45896119400d822ad7be5a3d5", "1111111111111111111111111111111111111111111111111111111111"},
	{"65e4ef6d196916e8d860f93692fc86057c51d8737a033ecc8338f35316645dc55b7505eb8cc05f83501032ff04d28e59a019e215f05d6ee076672b22198ab7a1", "11111111111111111111111111111111111111111111111111111111111"},
	{"864a668d13f625b71d091b922463abed0fd0c12f7a7cb3eca555e6c8e2c9340fc53be60932c85a43f9d4fc9fd6283fe316349d12c940f257e8b9843272a355a8", "111111111111111111111111111111111111111111111111111111111111"},
	{"1614c97345e38788881e7b5bd632cdeea514c23d0cb649024b32ddb3fc3a29d4fd36b7e6247566dc081aff7bdc343c7fefdab3a5837864bc7e7f71620a65c2d1", "1111111111111111111111111111111111111111111111111111111111111"},
	{"0b03d0ca8d199c9770ac23d69659f16a183041e167998942dac8a5e36d5e36a669f36faa7905e8d69a470168e295c150bf6bfc62be96df1b6a872fb152ab7c9c", "11111111111111111111111111111111111111111111111111111111111111"},
	{"448401d5fe535761e155306aaebb0b5779550906dbd9a34d00b5006cf32f9661ffc46245c59c5e32a551ba81eeccaa482ee7bcf03c13d58a9bfac6399f2b94c8", "111111111111111111111111111111111111111111111111111111111111111"},
	{"6723a63fc813efa037dab2128781cbc395a90ffd83bf2b520d6d62488350d898fd5624717ac2fa443388cb80fb7a784a04aa4fa6659c4fcce87e62dec718bb95", "1111111111111111111111111111111111111111111111111111111111111111"},
	{"b3c1fb2783d41ac463785fa06a43019d061a7ada06516fb0b9d7547f5ea5194fe9a90423d6b5439eaa425354a86f6bbeeea7edf2e8ae0c6fb02482bf944b8576", "11111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111"},
	{"70d3a8248c60b0ba3f33a908cd4d0f1222838abf2cff71a53098dd32387f004dabf73534835c7b9caa2d1ca39d4747ae3ee0a182f47f8386c18645c12c41c967", "111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111"},
	{"f16ddb94ff68cd33936dad110b0a841bcc9d7e489c848326d9c0edf15564ffbdb59d3436b45b45e10f57ab5750ebf2a53126be988476cf727b03641ba442118b", "1111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111"},
	{"0e8381d0b523d45cd129317e497c87f51fc47b023c8ba6ba3c0ff3307e663ca35c98edcb3bdc0c9fd21ce3cea4371109df68cc91d55b725bed7a2ebeb10e661f", "11111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111"},
	{"a7ee8984e60b34b35f5fbf91fa8af8f8644a62901797aca654f51b6dd97a72aed723dd5ea60b0fdad7979bac442b50fb98af532271deb54c2b2ea96313a02cf9", "111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111"},
	{"9308b12413b6d29a31c261bc94a2a6b603bf114e0fabcf26b0b1a2174d4088c41d41422d7cdba5a304185c4e1f0069b5c72be1eb68de3e96f24c8352b46fb3f3", "1111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111"},
	{"0008c0aab2eb0297d8a84dd4134122d6f979207840b163f413e82f0de0fb612053e70c90c4d60921b447e015b87c51ae9455e65ff832009aebde451b2176d559", "11111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111"},
	{"88275c81b599b1e973bf2498a8ce58104b54508035a11c4f3f73985d7438b7f5261c0089d3aa2e6b4e2f7ae22e6924a79078d02afc1608850b3f70b2d6cfaa7e", "111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111"},
	{"1af08e4ee1bf4faa7b2d429f9e9d8130edbfcae1120b31e4c3aafa63a1b465a40e6b79ca3f9f84576f848a5b19bbd1d1eba69153229af8d00ab700c90525a27d", "1111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111"},
	{"aecd6a988c19492bebf9ba3115c80c71546871e602f7253e6485702b3d6e3a4f1f1b268ab4e47e57f8157441c7c36782faa9ae14526f86aaa9dfcfaae07c4664", "11111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111"},
	{"b9aa2ed0e0ad16f56b577a81619efb66e6e52c2ad5f0a978063644306dafadce26671b1ae0039fcd9bc836c2d3d25ad59b2f647f6ad9dec68f5156036e0bdcfe", "111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111"},
	{"ce1f55ec8efb498920b008ff773fa722d4c908441412238c571032af6e47a9cfe14d2e3a336e4e53d337addae09a0524cbdac4af0f7e1ae70afb6d4fcd493b72", "1111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111"},
	{"ea4cac877cbc6caaf75c4846c577bd3ac6cfe44f792a70fa4b9f43671e95fa8d015149f2a007aed563ef4491d40c1e2639cf3be724baa4c801eeb97d9da265bf", "11111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111"},
	{"754a60a0fc302f33a0562f3d17e50711d4460c55eb71125485d73fbeb5e9f7b8139b7117a734ccbb05220d0c691c0d318bd32cfd1a6b2c9ac37b3174667b37b2", "111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111"},
	{"c947046f78ae3861db81c34e28ae056aa4c6b8385e2625a4a914c1f89a30ff111c4325f68149f0cbcd72b4b69aee82ebb384e43c9ab82d782da79b6692f6262f", "1111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111"},
	{"4e93a6e9505945164b02e8bd8df53e3bf9bf43faffcfb386972eedc8828662a95debd0cffadf658ccb17815327ddb7f24b3c818efb832f5bca1104355bce9b8b", "11111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111"},
	{"a1f050c7941148611bcbdea943e1b5fc9653af772d235a004c42e2871e2c3ef42214d9c03ca9f728e9853c16f8d31777099d9e8278021f51b3eda8d875610dd7", "111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111"},
	{"1f0ac4e2a57efc5459bc1d21a0e6502eec953f11021db44f62fd13a4c70000f04f71296224f3595f57ea5f99f61cc9bf9e81e8fd469b60961c45058fdf475f39", "1111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111"},
	{"610e0f364ac647d7a78be9e1e4b1f423132a5cb2fa94b0d8baa8d21d42639a77da897f3d8b3aec464b44d170eb9cf8020b6e4a377672bce649746be941a1d47d", "11111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111"},
	{"0f431aa36a3953f27987552b70ae548bf77be26b6100a710b0d870d7a5c538b9215e4dd6692b966f58b3710889adbd3fc4cab3a1618eb4d06b031e27f33ca3a1", "111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111"},
};

std::string toHex(const std::string& s)
{
	std::string ret(s.size() * 2, 0);
	for (size_t i = 0; i < s.size(); i++) {
		cybozu::itohex(&ret[i * 2], 2, uint8_t(s[i]), false);
	}
	return ret;
}

typedef std::vector<uint8_t> Uint8Vec;

Uint8Vec fromHex(const std::string& s)
{
	Uint8Vec ret(s.size() / 2);
	for (size_t i = 0; i < s.size(); i += 2) {
		ret[i / 2] = cybozu::hextoi(&s[i], 2);
	}
	return ret;
}

CYBOZU_TEST_AUTO(sha256)
{
	for (size_t i = 0; i < CYBOZU_NUM_OF_ARRAY(sha256Tbl); i++) {
		const char *msg = sha256Tbl[i].in;
		std::string md = toHex(cybozu::Sha256().digest(msg, strlen(msg)));
		CYBOZU_TEST_EQUAL(md, sha256Tbl[i].out);
		char buf[32];
		CYBOZU_BENCH_C("sha256", 100000, cybozu::Sha256().digest, buf, sizeof(buf), msg, strlen(msg));
	}
}

CYBOZU_TEST_AUTO(sha512)
{
	for (size_t i = 0; i < CYBOZU_NUM_OF_ARRAY(sha512Tbl); i++) {
		const char *msg = sha512Tbl[i].in;
		std::string md = toHex(cybozu::Sha512().digest(msg, strlen(msg)));
		CYBOZU_TEST_EQUAL(md, sha512Tbl[i].out);
	}
}

const struct HmacTbl {
	const char *key;
	const char *msg;
	const char *mac;
} hmac256Tbl[] = {
	{
		"0b0b0b0b0b0b0b0b0b0b0b0b0b0b0b0b0b0b0b0b",
	    "4869205468657265",
	    "b0344c61d8db38535ca8afceaf0bf12b881dc200c9833da726e9376c2e32cff7",
	},
	{
		"",
		"",
		"b613679a0814d9ec772f95d778c35fc5ff1697c493715653c6c712144292c5ad"
	},
	{
		"4a656665",
		"7768617420646f2079612077616e7420666f72206e6f7468696e673f",
		"5bdcc146bf60754e6a042426089575c75a003f089d2739839dec58b964ec3843",
	},
	{
		"aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa",
		"dddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddd",
		"773ea91e36800e46854db8ebd09181a72959098b3ef8c122d9635514ced565fe",
	},
	{
		"aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa",
		"54657374205573696e67204c6172676572205468616e20426c6f636b2d53697a65204b6579202d2048617368204b6579204669727374",
		"60e431591ee0b67f0d8a26aacbf5b77f8e0bc6213728c5140546040f0ee37f54",
	},
	{
		"aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa",
		"5468697320697320612074657374207573696e672061206c6172676572207468616e20626c6f636b2d73697a65206b657920616e642061206c6172676572207468616e20626c6f636b2d73697a6520646174612e20546865206b6579206e6565647320746f20626520686173686564206265666f7265206265696e6720757365642062792074686520484d414320616c676f726974686d2e",
		"9b09ffa71b942fcb27635fbcd5b0e944bfdc63644f0713938a7f51535c3a35e2",
	},
	{
		"01010101010101010101010101010101010101010101010101010101010101010101010101010101010101010101010101010101010101010101010101010101",
		"12",
		"9fc5fd7acf75bf2125220240293bd8221d72a25ffb5bfb397ee1a2a00df7a1ad",
	},
	{
		"0101010101010101010101010101010101010101010101010101010101010101010101010101010101010101010101010101010101010101010101010101010101",
		"12",
		"4a8ac5b5f14061a2ed19ea9ac716b3c2c27343ac4dc52e42fabb9b1ab019d335",
	},
	{
		"010101010101010101010101010101010101010101010101010101010101010101010101010101010101010101010101010101010101010101010101010101010101",
		"12",
		"e4ab292c53a535617d5d5a80a74de6e5e2516faba8708ac536a5bb79c7c8e989",
	},
};

CYBOZU_TEST_AUTO(hmac256)
{
	for (size_t i = 0; i < CYBOZU_NUM_OF_ARRAY(hmac256Tbl); i++) {
		char hmac[32];
		Uint8Vec key, msg;
		key = fromHex(hmac256Tbl[i].key);
		msg = fromHex(hmac256Tbl[i].msg);
		cybozu::hmac256(hmac, key.data(), key.size(), msg.data(), msg.size());
		std::string h = toHex(std::string(hmac, sizeof(hmac)));
		CYBOZU_TEST_EQUAL(h, hmac256Tbl[i].mac);
	}
}

